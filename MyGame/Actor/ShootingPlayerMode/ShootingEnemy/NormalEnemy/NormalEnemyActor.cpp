#include "NormalEnemyActor.h"
#include "../Sound/Sound.h"
#include "../Actor/CommonUIActor/Effect2D/Effect2D.h"
#include "../Actor/ShootingPlayerMode/ItemActor/ItemCreater/ItemCreater.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/EnemyHeadShot/EnemyHeadShot.h"
#include "NormalEnemyMotionNum.h"
#include "NormalEnemyStateInc.h"
#include "../Actor/EnemyCommon/EnemyParameter.h"

NormalEnemyActor::NormalEnemyActor(int model, IWorld * world, const Vector3 & position, const Matrix & rotation, const IBodyPtr & body):
	Actor(world,"NormalEnemy",position,rotation, body),
	player_{nullptr},
	mesh_{model},
	mroarCheck{false},
	mDamageParam{ 1 },
	mAttackCheck{false}
{
	mcurrentStateID = ActorStateID::NormalEnemyIdle;
	normalenemyState_[ActorStateID::NormalEnemyIdle].add(add_state<NormalEnemyIdle>(world, parameters_));
	normalenemyState_[ActorStateID::NormalEnemyDamage].add(add_state<NormalEnemyDamage>(world, parameters_));
	normalenemyState_[ActorStateID::NormalEnemyDead].add(add_state<NormalEnemyDead>(world, parameters_));
	normalenemyState_[ActorStateID::NormalEnemyPunch].add(add_state<NormalEnemyPunch>(world, parameters_));
	normalenemyState_[ActorStateID::NormalEnemyRoar].add(add_state<NormalEnemyRoar>(world, parameters_));

	normalenemyState_[mcurrentStateID].initialize();

	initialize();
}

void NormalEnemyActor::initialize()
{
	mesh_.transform(Getpose());

	parameters_.Set_Position(position_);
	parameters_.Set_HP(NormalEnemyHP);
	parameters_.Set_Motion(NormalEnemyMotionNum::MotionNormalEnemyIdel);

	auto EH = new_actor<EnemyHeadShot>(world_, position_, weak_from_this());
	world_->add_actor(ActorGroup::EnemyHead, EH);
	m_HS = EH;
}

void NormalEnemyActor::update(float deltaTime)
{
	//ステイトクラスの情報を更新する
	normalenemyState_[mcurrentStateID].update(position_, rotation_, mesh_);

	//ステイトが変わった際に呼び出される
	if (normalenemyState_[mcurrentStateID].Get_NextStateFlag())
	{
		parameters_.Set_PreveStateID(parameters_.Get_StateID());
		normalenemyState_[mcurrentStateID].NextState(mcurrentStateID);
		normalenemyState_[mcurrentStateID].initialize();
		parameters_.Set_StateID(mcurrentStateID);
		parameters_.Set_Statetimer(0.0f);
	}
	//エネミーのポジションをヘッドショットのアクターに送信する
	m_HS.lock()->receiveMessage(EventMessage::GETENEMYPOS, reinterpret_cast<void*>(&(position_ + HSPos)));

	//壁床との当たり判定
	collision();

	//ポーズ中は返す
	if (world_->GetPauseCheck() == true) return;

	//死んでいる状態
	if (parameters_.Get_IsDead() == true)
	{
		//アイテムを生成する
		world_->add_actor(ActorGroup::Item, std::make_shared<ItemCreater>(world_, position_));

		//ヘッドショットの当たり判定を削除するメッセージ
		m_HS.lock()->receiveMessage(EventMessage::DEAD_DUMMY_ENEMY, nullptr);
		die();
		return;
	}

	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(parameters_.Get_Motion());

	//重力
	mG.gravity(position_, velocity_, Floorcollide);

	//プレイヤーの取得
	getPlayer();

	//敵の攻撃を食らったら点滅させる
	invincibly(parameters_.Get_invincibly());

	//状態時間を加算
	parameters_.Add_Statetime(0.5f);

	//移動中にプレイヤー方を向く
	if (parameters_.Get_StateID() == ActorStateID::NormalEnemyIdle)
	{
		mEV.Move(position_, player_->Getposition(), 0.5f, mAttackCheck,15.0f);
		Attacking();
	}
}

void NormalEnemyActor::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();

	if(mAttackCheck)
	DrawFormatString(500, 500, GetColor(255, 255, 255), "hit");

}

void NormalEnemyActor::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (int*)&hitdir);
}

void NormalEnemyActor::receiveMessage(EventMessage message, void * param)
{
	//プレイヤーと接触したときに重ならないように押し出す
	if (message == EventMessage::HIT_PLAYER)
	{
		velocity_ = mAP.Hit(*static_cast<Vector3*>(param));
	}

	//プレイヤーの弾威力をもらう
	if (message == EventMessage::DAMAGEPARAM)
	{
		mDamageParam = *static_cast<int*>(param);
	}

	//無敵時間でないときにダメージを受ける
	if (parameters_.Get_invincibly() == false)
	{
		if (message == EventMessage::HIT_BALL)
		{
			BulletHit(mDamageParam);
		}
		if (message == EventMessage::HIT_BALL_HEAD)
		{
			BulletHit(3);
		}

		if (message == EventMessage::HIT_PLAYER_PUNCH)
		{
			parameters_.Red_HP(*static_cast<int*>(param));
			parameters_.Set_Invicibly(true);
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::ATTACK_SE);
		}
	}

}

void NormalEnemyActor::collision()
{
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		position_.x = result.x;
		position_.z = result.z;
		Stagecollide = true;
	}
	else {
		Stagecollide = false;
	}

	//床との接地判定
	if (floor(result)) {
		Floorcollide = true;
		position_ = result + rotation_.Up()*(body_->length()*0.7f + body_->radius()*0.7f);
	}
	else {
		Floorcollide = false;
	}
}

void NormalEnemyActor::getPlayer()
{
	//プレイヤーの取得
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void NormalEnemyActor::Attacking()
{
	float PlayerAngle = mPL.Look(player_, position_, rotation_);

	if (MathHelper::Abs(PlayerAngle) < 0.2f && mAttackCheck)
	{
		parameters_.Set_Attack(true);
		return;
	}

	//プレイヤー側に回転させる
	rotation_ *= Matrix::CreateRotationY(PlayerAngle);
}

void NormalEnemyActor::BulletHit(int damage)
{
	parameters_.Red_HP(damage);
	parameters_.Set_Invicibly(true);

	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DAMAGEENEMY_SE);
}

void NormalEnemyActor::invincibly(bool check)
{
	//モデルを点滅させる
	if (check) {
		ActorTransparence();
	}
	else {
		TransparenceInit();
	}
}
