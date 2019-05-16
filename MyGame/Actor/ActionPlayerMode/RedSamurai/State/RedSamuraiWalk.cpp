#include "RedSamuraiWalk.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"

RedSamuraiWaik::RedSamuraiWaik(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void RedSamuraiWaik::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraiWalk;

	parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiForWard);

	mAttackTime = 180.0f;
}

void RedSamuraiWaik::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//�v���C���[�̌���
	auto player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	//�v���C���[�Ɍ������Ĉړ�����
	Movement(lposition);
	//���Ԋu�ōU����Ԃ�
	AttackTimeCheck(lposition,lrotation);

	//HP���O�ɂȂ����玀�S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::RedSamuraiDead;
		mNextStateFlag = true;
		return;
	}
}

void RedSamuraiWaik::Movement(Vector3 lposition)
{
	//�v���C���[�̌���
	auto player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	//�v���C���[�Ƃ̋���
	const float PlayerDis = Vector3::Distance(lposition, player_->Getposition());

	//������15�ȉ��͂���ȏ��ɍs���Ȃ�
	if (PlayerDis <= 15.0f) return;

	//�v���C���[�ւ̃x�N�g��
	const Vector3 playervec = Vector3(player_->Getposition().x - lposition.x, player_->Getposition().y - lposition.y, player_->Getposition().z - lposition.z).Normalize();
	parameters_->Set_Position(lposition + playervec * WalkSpeed);
}

void RedSamuraiWaik::AttackTimeCheck(Vector3 lposition, Matrix lrotation)
{
	//�p�x���Ԃ��O�ɂȂ�����U����Ԃ�
	mAttackTime -= 1.0f;
	if (mAttackTime < 0)
	{
		mNextStateID = ActorStateID::RedSamuraiAttack;
		mNextStateFlag = true;
		return;
	}

}