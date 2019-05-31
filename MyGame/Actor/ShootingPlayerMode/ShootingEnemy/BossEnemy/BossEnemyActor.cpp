#include "BossEnemyActor.h"
#include "../Sound/Sound.h"
#include "../Actor/CommonUIActor/Effect2D/Effect2D.h"
#include "../Actor/ShootingPlayerMode/ItemActor/ItemCreater/ItemCreater.h"
#include "BossEnemyMotionNum.h"
#include "BossEnemyStateInc.h"
#include "../Game/Define.h"
#include "../Scene/GameData/GameDataManager.h"

BossEnemyActor::BossEnemyActor(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body) :
	Actor(world, "BossEnemy", position, body),
	player_{ nullptr },
	mesh_{ model },
	mroarCheck{ false },
	mDamageParam{ 1 },
	mAttackCheck{ false },
	mAttackTime{mAttackTimeInit}
{
	mcurrentStateID = ActorStateID::BossEnemyIdle;
	bossenemyState_[ActorStateID::BossEnemyIdle].add(add_state<BossEnemyIdle>(world, parameters_));
	bossenemyState_[ActorStateID::BossEnemyDamage].add(add_state<BossEnemyDamage>(world, parameters_));
	bossenemyState_[ActorStateID::BossEnemyDead].add(add_state<BossEnemyDead>(world, parameters_));
	bossenemyState_[ActorStateID::BossEnemyPunch].add(add_state<BossEnemyPunch>(world, parameters_));
	bossenemyState_[ActorStateID::BossEnemyFire].add(add_state<BossEnemyFire>(world, parameters_));
	bossenemyState_[ActorStateID::BossEnemyFireBefo].add(add_state<BossEnemyFireBefo>(world, parameters_));

	bossenemyState_[mcurrentStateID].initialize();

	initialize();
}

void BossEnemyActor::initialize()
{
	mesh_.transform(Getpose());

	parameters_.Set_Position(position_);
	parameters_.Set_HP(BossHPVal);
	parameters_.Set_StateID(ActorStateID::BossEnemyIdle);
	parameters_.Set_Motion(BossEnemyMotion::MotionBossIdle);
}

void BossEnemyActor::update(float deltaTime)
{
	//ステイトクラスの情報を更新する
	bossenemyState_[mcurrentStateID].update(position_, rotation_, mesh_);

	//ステイトが変わった際に呼び出される
	if (bossenemyState_[mcurrentStateID].Get_NextStateFlag())
	{
		parameters_.Set_PreveStateID(parameters_.Get_StateID());
		bossenemyState_[mcurrentStateID].NextState(mcurrentStateID);
		bossenemyState_[mcurrentStateID].initialize();
		parameters_.Set_StateID(mcurrentStateID);
		parameters_.Set_Statetimer(0.0f);
	}

	//壁床との当たり判定
	collision();

	//ポーズ中は返す
	if (world_->GetPauseCheck() == true) return;

	//死んでいる状態
	if (parameters_.Get_IsDead() == true)
	{
		GameDataManager::getInstance().SetDeadBossEnemy(true);
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
	if (parameters_.Get_StateID() == ActorStateID::BossEnemyIdle)
	{
		float movespeed = 0.5f;
		if (parameters_.Get_HP() < 5) {
			movespeed = 0.8f;
			parameters_.Set_Motion(BossEnemyMotion::MotionBossRun);
		}
		else {
			parameters_.Set_Motion(BossEnemyMotion::MotionBossWalk);
		}
		mEV.Move(position_, player_->Getposition(), movespeed, mAttackCheck, 15.0f);
		Attacking();
	}
}

void BossEnemyActor::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();

	mBH.draw(parameters_.Get_HP(),Vector3(position_.x,position_.y + 25.0f,position_.z));
}

void BossEnemyActor::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (int*)&hitdir);
}

void BossEnemyActor::receiveMessage(EventMessage message, void * param)
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
		if (message == EventMessage::HIT_PLAYER_PUNCH)
		{
			parameters_.Red_HP(*static_cast<int*>(param));
			parameters_.Set_Invicibly(true);
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::ATTACK_SE);
		}
	}

}

void BossEnemyActor::collision()
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
		position_ = result + rotation_.Up()*(body_->length()*0.7f + body_->radius()*0.467f);
	}
	else {
		Floorcollide = false;
	}
}

void BossEnemyActor::getPlayer()
{
	//プレイヤーの取得
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void BossEnemyActor::Attacking()
{
	float PlayerAngle = mPL.Look(player_, position_, rotation_);

	mAttackTime--;
	if (MathHelper::Abs(PlayerAngle) < 0.2f && (mAttackCheck || mAttackTime < 0))
	{
		if (mAttackCheck) {
			parameters_.Set_AttackType(1);
			return;
		}
		if (mAttackTime < 0){
			parameters_.Set_AttackType(2);
			mAttackTime = mAttackTimeInit;
			return;
		}
	}

	//プレイヤー側に回転させる
	rotation_ *= Matrix::CreateRotationY(PlayerAngle);
}

void BossEnemyActor::BulletHit(int damage)
{
	parameters_.Red_HP(damage);
	parameters_.Set_Invicibly(true);

	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DAMAGEENEMY_SE);
}

void BossEnemyActor::invincibly(bool check)
{
	//モデルを点滅させる
	if (check) {
		ActorTransparence();
	}
	else {
		TransparenceInit();
	}
}
