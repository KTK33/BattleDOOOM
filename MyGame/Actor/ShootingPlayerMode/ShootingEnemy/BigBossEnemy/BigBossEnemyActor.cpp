#include "BigBossEnemyActor.h"
#include "BigBossEnemyStateInc.h"
#include "BigBossEnemyMotionNum.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Sound/Sound.h"
#include "HPUI/BigBossHPUI.h"
#include "BigBossEnemyParam/BigBossEnemyParam.h"

BigBossEnemyActor::BigBossEnemyActor(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world, "BigBossEnemy", position, body),
	player_{ nullptr },
	mesh_{ model },
	mDamageParam{ 1 },
	mAttackTime{mAttackTimeInit},
	mAttack{ false }
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

	BigBossEnemyParam::getInstance().initialize();

	world_->add_actor(ActorGroup::UI, new_actor<BigBossHPUI>(world_));
}

void BigBossEnemyActor::update(float deltaTime)
{
	//�X�e�C�g�N���X�̏����X�V����
	bigbossenemyState_[mcurrentStateID].update(position_, rotation_, mesh_);

	//�X�e�C�g���ς�����ۂɌĂяo�����
	if (bigbossenemyState_[mcurrentStateID].Get_NextStateFlag())
	{
		parameters_.Set_PreveStateID(parameters_.Get_StateID());
		bigbossenemyState_[mcurrentStateID].NextState(mcurrentStateID);
		bigbossenemyState_[mcurrentStateID].initialize();
		parameters_.Set_StateID(mcurrentStateID);
		parameters_.Set_Statetimer(0.0f);
	}

	//�Ǐ��Ƃ̓����蔻��
	collision();

	//�|�[�Y���͕Ԃ�
	if (world_->GetPauseCheck() == true) return;

	//����ł�����
	if (parameters_.Get_IsDead() == true)
	{
		GameDataManager::getInstance().SetDeadBossEnemy(true);
		die();
		return;
	}

	//�d��
	mG.gravity(position_, velocity_, Floorcollide);

	//�v���C���[�̎擾
	getPlayer();

	if (mcurrentStateID == ActorStateID::BigBossEnemyIdle)
	{
		LookPlayer();
		Attacking();

		mEM.Move(position_, player_->Getposition(), BigBossWalkSpeed, mAttack, 15.0f);
	}
	else if (mcurrentStateID == ActorStateID::BigBossEnemyAttack)
	{
		if (!BigBossEnemyParam::getInstance().Get_RotaCheck()){
			LookPlayer();
		}
	}

	//��Ԏ��Ԃ����Z
	parameters_.Add_Statetime(0.5f);

	int hp = parameters_.Get_HP();
	world_->send_message(EventMessage::BOSSHP, reinterpret_cast<int*>(&hp));

	mesh_.update(deltaTime);
	mesh_.transform(Matrix::CreateScale(Vector3(1.7f,1.7f,1.7f)) *Getpose());
	mesh_.change_motion(parameters_.Get_Motion());
}

void BigBossEnemyActor::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}

void BigBossEnemyActor::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (int*)&hitdir);
}

void BigBossEnemyActor::receiveMessage(EventMessage message, void * param)
{
	//�v���C���[�ƐڐG�����Ƃ��ɏd�Ȃ�Ȃ��悤�ɉ����o��
	if (message == EventMessage::HIT_PLAYER)
	{
		velocity_ = mAP.Hit(*static_cast<Vector3*>(param));
	}

	//�v���C���[�̒e�З͂����炤
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
	//�Ԃ�������
	Vector3 result;
	//���Ƃ̐ڒn����
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
	//�v���C���[�̎擾
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void BigBossEnemyActor::LookPlayer()
{
	float PlayerAngle = mPL.Look(player_, position_, rotation_);
	//�v���C���[���ɉ�]������
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