#include "NormalEnemyActor.h"
#include "../Sound/Sound.h"
#include "../Actor/CommonUIActor/Effect2D/Effect2D.h"
#include "../Actor/ShootingPlayerMode/ItemActor/ItemCreater/ItemCreater.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/EnemyHeadShot/EnemyHeadShot.h"
#include "NormalEnemyMotionNum.h"
#include "NormalEnemyStateInc.h"
#include "../Game/Define.h"

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
	parameters_.Set_HP(NormalHPVal);
	parameters_.Set_Motion(NormalEnemyMotionNum::MotionNormalEnemyIdle);

	auto EH = new_actor<EnemyHeadShot>(world_, position_, weak_from_this());
	world_->add_actor(ActorGroup::EnemyHead, EH);
	m_HS = EH;
}

void NormalEnemyActor::update(float deltaTime)
{
	//�X�e�C�g�N���X�̏����X�V����
	normalenemyState_[mcurrentStateID].update(position_, rotation_, mesh_);

	//�X�e�C�g���ς�����ۂɌĂяo�����
	if (normalenemyState_[mcurrentStateID].Get_NextStateFlag())
	{
		parameters_.Set_PreveStateID(parameters_.Get_StateID());
		normalenemyState_[mcurrentStateID].NextState(mcurrentStateID);
		normalenemyState_[mcurrentStateID].initialize();
		parameters_.Set_StateID(mcurrentStateID);
		parameters_.Set_Statetimer(0.0f);
	}
	//�G�l�~�[�̃|�W�V�������w�b�h�V���b�g�̃A�N�^�[�ɑ��M����
	m_HS.lock()->receiveMessage(EventMessage::GETENEMYPOS, reinterpret_cast<void*>(&(position_ + HSPos)));

	//�Ǐ��Ƃ̓����蔻��
	collision();

	//�|�[�Y���͕Ԃ�
	if (world_->GetPauseCheck() == true) return;

	//����ł�����
	if (parameters_.Get_IsDead() == true)
	{
		//�A�C�e���𐶐�����
		world_->add_actor(ActorGroup::Item, std::make_shared<ItemCreater>(world_, position_));

		//�w�b�h�V���b�g�̓����蔻����폜���郁�b�Z�[�W
		m_HS.lock()->receiveMessage(EventMessage::DEAD_DUMMY_ENEMY, nullptr);
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
}

void NormalEnemyActor::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (int*)&hitdir);
}

void NormalEnemyActor::receiveMessage(EventMessage message, void * param)
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
		position_ = result + rotation_.Up()*(body_->length()*0.7f + body_->radius()*0.7f);
	}
	else {
		Floorcollide = false;
	}
}

void NormalEnemyActor::getPlayer()
{
	//�v���C���[�̎擾
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

	//�v���C���[���ɉ�]������
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
	//���f����_�ł�����
	if (check) {
		ActorTransparence();
	}
	else {
		TransparenceInit();
	}
}
