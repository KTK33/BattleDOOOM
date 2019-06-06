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
	//�X�e�C�g�N���X�̏����X�V����
	bossenemyState_[mcurrentStateID].update(position_, rotation_, mesh_);

	//�X�e�C�g���ς�����ۂɌĂяo�����
	if (bossenemyState_[mcurrentStateID].Get_NextStateFlag())
	{
		parameters_.Set_PreveStateID(parameters_.Get_StateID());
		bossenemyState_[mcurrentStateID].NextState(mcurrentStateID);
		bossenemyState_[mcurrentStateID].initialize();
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

	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(parameters_.Get_Motion());

	//�d��
	mG.gravity(position_, velocity_, Floorcollide);

	//�v���C���[�̎擾
	getPlayer();

	//�G�̍U����H�������_�ł�����
	invincibly(parameters_.Get_invincibly());

	//��Ԏ��Ԃ����Z
	parameters_.Add_Statetime(0.5f);

	//�ړ����Ƀv���C���[��������
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

	//���G���ԂłȂ��Ƃ��Ƀ_���[�W���󂯂�
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
	//�Ԃ�������
	Vector3 result;
	//�ǂƂԂ��Ă���
	if (field(result)) {
		position_.x = result.x;
		position_.z = result.z;
		Stagecollide = true;
	}
	else {
		Stagecollide = false;
	}

	//���Ƃ̐ڒn����
	if (floor(result)) {
		Floorcollide = true;
		position_ = result + rotation_.Up()*mpushheight;
	}
	else {
		Floorcollide = false;
	}
}

void BossEnemyActor::getPlayer()
{
	//�v���C���[�̎擾
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

	//�v���C���[���ɉ�]������
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
	//���f����_�ł�����
	if (check) {
		ActorTransparence();
	}
	else {
		TransparenceInit();
	}
}
