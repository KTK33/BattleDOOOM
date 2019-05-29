#include "RedSamuraiAttack.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"
#include "../Actor/ActionPlayerMode/RedSamurai/Arrow/ArrowAttack.h"
#include "../Actor/EnemyAttackCollison/EnemyAttackCollison.h"
#include "../Sound/Sound.h"

RedSamuraiAttack::RedSamuraiAttack(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void RedSamuraiAttack::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraiAttack;

	mAttackAlready = false;
	mAttckStart = false;
	mAttckType = 0;
}

void RedSamuraiAttack::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//��x�����U���̑I��������
	if (!mAttackAlready)
	{
		AttackBehavior(lposition, lrotation);
	}
	mAttackAlready = true;

	//���[�V�����̎��Ԃɂ���ē����蔻��𐶐�
	if (mAttckStart)
	{
		if (mAttckType < 7) {
			parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiAttack1);
			if (parameters_->Get_Statetimer() == 20.0f)AttackCollision(lposition, lrotation, 15, 1, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
			if (parameters_->Get_Statetimer() == 40.0f)AttackCollision(lposition, lrotation, 15, 2, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
			if (parameters_->Get_Statetimer() == 60.0f)AttackCollision(lposition, lrotation, 15, 2, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
		}
		else {
			parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiAttack2);
			if (parameters_->Get_Statetimer() == 60.0f)AttackCollision(lposition, lrotation, 30, 5, Vector3(0.0f, 13.0f, 0.0f), 2.0f, 2.5f);
		}
	}

	//���[�V�����̎��Ԃ��I�������ړ���Ԃ�
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_Attack(false);
		mNextStateID = ActorStateID::RedSamuraiIdel;
		mNextStateFlag = true;
		return;
	}

	//HP���O�ɂȂ����玀�S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::RedSamuraiDead;
		mNextStateFlag = true;
		return;
	}
}

void RedSamuraiAttack::AttackBehavior(Vector3 lposition, Matrix lrotation)
{
	//�v���C���[�̌���
	auto player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	//�v���C���[�Ƃ̋���
	const float PlayerDis = Vector3::Distance(lposition, player_->Getposition());

	//������30�ȏ�Ȃ牓�����U���A����ȊO�͋ߋ����U��
	if (PlayerDis >= 15.0f)
	{
		world_->add_actor(ActorGroup::EnemyBullet, std::make_shared<ArrowAttack>(52, world_, Vector3{ lposition.x,lposition.y + 13.0f,lposition.z } +lrotation.Forward() * 4 + lrotation.Right() * 3));
		parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiArrowAttack);
		parameters_->Set_Statetimer(0.0f);
	}
	else
	{
		mAttckStart = true;
		//�m���ōU���ω�
		mAttckType = Random::rand(0, 10);
		parameters_->Set_Statetimer(0.0f);
	}
}

void RedSamuraiAttack::AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad)
{
	//�U�������蔻��̐���
	auto AttackPunch = std::make_shared<EnemyAttackCollison>(world_, Vector3{ lposition + lrotation.Forward() * 10 },
		std::make_shared<BoundingCapsule>(spot, Matrix::Identity, len, rad));
	world_->add_actor(ActorGroup::EnemyBullet, AttackPunch);
	AttackPunch->SetParam(false, deadTime, attackParam);

	Sound::GetInstance().PlaySE(SE_ID::RED_SWARD);

}