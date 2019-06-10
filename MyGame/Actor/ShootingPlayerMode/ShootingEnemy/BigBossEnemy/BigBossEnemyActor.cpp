#include "BigBossEnemyActor.h"
#include "BigBossEnemyStateInc.h"
#include "BigBossEnemyMotionNum.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Sound/Sound.h"
#include "HPUI/BigBossHPUI.h"

BigBossEnemyActor::BigBossEnemyActor(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world, "BigBossEnemy", position, body),
	player_{ nullptr },
	mesh_{ model },
	mDamageParam{ 1 },
	mAttackTime{mAttackTimeInit}
{
	mcurrentStateID = ActorStateID::BigBossEnemyIdle;
	bigbossenemyState_[ActorStateID::BigBossEnemyIdle].add(add_state<BigBossEnemyIdle>(world, parameters_));
	bigbossenemyState_[ActorStateID::BigBossEnemyAttack].add(add_state<BigBossEnemyAttack>(world, parameters_));
	bigbossenemyState_[ActorStateID::BigBossEnemyDead].add(add_state<BigBossEnemyDead>(world, parameters_));

	bigbossenemyState_[mcurrentStateID].initialize();

	initialize();
}

void BigBossEnemyActor::initialize()
{
	mesh_.transform(Getpose());

	parameters_.Set_Position(position_);
	parameters_.Set_HP(BigBossHPVal);
	parameters_.Set_StateID(ActorStateID::BigBossEnemyIdle);

	world_->add_actor(ActorGroup::UI, new_actor<BigBossHPUI>(world_));
}

void BigBossEnemyActor::update(float deltaTime)
{
	//ステイトクラスの情報を更新する
	bigbossenemyState_[mcurrentStateID].update(position_, rotation_, mesh_);

	//ステイトが変わった際に呼び出される
	if (bigbossenemyState_[mcurrentStateID].Get_NextStateFlag())
	{
		parameters_.Set_PreveStateID(parameters_.Get_StateID());
		bigbossenemyState_[mcurrentStateID].NextState(mcurrentStateID);
		bigbossenemyState_[mcurrentStateID].initialize();
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

	if (mcurrentStateID == ActorStateID::BigBossEnemyIdle)
	{
		LookPlayer();
		Attacking();
	}

	//状態時間を加算
	parameters_.Add_Statetime(0.5f);

	int hp = parameters_.Get_HP();
	world_->send_message(EventMessage::BOSSHP, reinterpret_cast<int*>(&hp));
}

void BigBossEnemyActor::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();

	SetFontSize(32);
	DrawFormatString(300, 200, GetColor(255, 0, 0), "%f,%f,%f", position_.x, position_.y, position_.z);
}

void BigBossEnemyActor::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (int*)&hitdir);
}

void BigBossEnemyActor::receiveMessage(EventMessage message, void * param)
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

	if (message == EventMessage::HIT_BALL)
	{
		BulletHit(mDamageParam);
	}

	if (message == EventMessage::HIT_PLAYER_PUNCH)
	{
		parameters_.Red_HP(*static_cast<int*>(param));
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::ATTACK_SE);
	}
}

void BigBossEnemyActor::collision()
{
	//ぶつかったか
	Vector3 result;
	//床との接地判定
	if (floor(result)) {
		Floorcollide = true;
		position_ = result + rotation_.Up()*mpushheight;
	}
	else {
		Floorcollide = false;
	}
}

void BigBossEnemyActor::getPlayer()
{
	//プレイヤーの取得
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void BigBossEnemyActor::LookPlayer()
{
	float PlayerAngle = mPL.Look(player_, position_, rotation_);
	//プレイヤー側に回転させる
	rotation_ *= Matrix::CreateRotationY(PlayerAngle);
}

void BigBossEnemyActor::Attacking()
{
	mAttackTime--;
	if (mAttackTime <= 0)
	{
		parameters_.Set_Attack(true);
		mAttackTime = mAttackTimeInit;
	}
}

void BigBossEnemyActor::BulletHit(int damage)
{
	parameters_.Red_HP(damage);
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DAMAGEENEMY_SE);
}