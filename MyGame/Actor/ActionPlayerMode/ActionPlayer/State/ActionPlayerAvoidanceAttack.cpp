#include "ActionPlayerAvoidanceAttack.h"
#include "../ActionPlayerMotionNum.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActionPlayerMode/ActionPlayer/ActionPlayerMotionNum.h"
#include "../Actor/PlayerAttackCollision/PlayerAttackCollision.h"
#include "../Input/InputInfoInc.h"

ActionPlayerAvoidanceAttack::ActionPlayerAvoidanceAttack(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ActionPlayerAvoidanceAttack::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerAvoidanceAttack;

	parameters_->Set_Motion(ActionPlayerMotion::MotionPlayerAvoidanceAttack);
}

void ActionPlayerAvoidanceAttack::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//�U��
	AttackOption(lposition, lrotation);

	//���͏��
	Input();

	//���[�V�����̎��Ԃ��I�������ړ���Ԃ�
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::ActionPlayerIdel;
		mNextStateFlag = true;
		return;
	}

	//HP���O�ɂȂ����玀�S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::ActionPlayerDead;
		mNextStateFlag = true;
		return;
	}
}

void ActionPlayerAvoidanceAttack::AttackOption(Vector3 lposition, Matrix lrotation)
{
	if(parameters_->Get_Statetimer() == 25.0f)AttackCollision(lposition, lrotation, 20, 1, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
	if(parameters_->Get_Statetimer() == 40.0f)AttackCollision(lposition, lrotation, 20, 2, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);

}

void ActionPlayerAvoidanceAttack::AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad)
{
	//�U�������蔻��̐���
	auto AttackPunch = std::make_shared<PlayerAttackCollision>(world_, Vector3{ lposition + lrotation.Forward() * 10 },
		std::make_shared<BoundingCapsule>(spot, Matrix::Identity, len, rad));
	world_->add_actor(ActorGroup::PlayerBullet, AttackPunch);
	AttackPunch->SetParam(false, deadTime, attackParam);
}

void ActionPlayerAvoidanceAttack::Input()
{
	//�X�e�b�v
	if(ButtonA::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ActionPlayerAvoidance;
		mNextStateFlag = true;
		return;
	}
}
