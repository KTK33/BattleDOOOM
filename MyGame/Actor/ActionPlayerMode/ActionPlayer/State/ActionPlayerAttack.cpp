#include "ActionPlayerAttack.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActionPlayerMode/ActionPlayer/ActionPlayerMotionNum.h"
#include "../Actor/PlayerAttackCollision/PlayerAttackCollision.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"

ActionPlayerAttack::ActionPlayerAttack(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ActionPlayerAttack::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerAttack;

	parameters_->Set_Motion(ActionPlayerMotion::MotionPlayerAttack1);
	
	mAttackCount = 1;
}

void ActionPlayerAttack::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//���[�V�����̏I���20�t���[���O�܂łɍU���{�^���������Ύ��̍U��������
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 10 && mAttackCount < 2)
	{
		Attack();
	}

	//�U���̑I��
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

void ActionPlayerAttack::Attack()
{
	if (GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM2) || 
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		parameters_->Set_Statetimer(0.0f);
		mAttackCount += 1;
		switch (mAttackCount) {
		case 2:
			parameters_->Set_Motion(ActionPlayerMotion::MotionPlayerAttack2); break;
		case 3:
			parameters_->Set_Motion(ActionPlayerMotion::MotionPlayerAttack3); break;
		default:break;
		}
	}
}

void ActionPlayerAttack::AttackOption(Vector3 lposition, Matrix lrotation)
{
	//�U���R���{�񐔂ɂ���ē����蔻��̐����^�C�~���O��ς���
	switch (mAttackCount) {
	case 1:
		if (parameters_->Get_Statetimer() == 38.0f)AttackCollision(lposition, lrotation, 20, 1, Vector3(0.0f, 13.0f, 0.0f), 2.5f, 3.5f); break;
	case 2:
		if (parameters_->Get_Statetimer() == 5.0f) AttackCollision(lposition, lrotation, 20, 2, Vector3(0.0f, 13.0f, 0.0f), 2.5f, 3.5f); break;
	case 3:
		if (parameters_->Get_Statetimer() == 5.0f) AttackCollision(lposition, lrotation, 20, 3, Vector3(0.0f, 13.0f, 0.0f), 2.5f, 3.5f); break;
	default:
		break;
	}

}

void ActionPlayerAttack::AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad)
{
	//�U�������蔻��̐���
	auto AttackPunch = std::make_shared<PlayerAttackCollision>(world_, Vector3{ lposition + lrotation.Forward() * 10 },
		std::make_shared<BoundingCapsule>(spot, Matrix::Identity, len, rad));
	world_->add_actor(ActorGroup::PlayerBullet, AttackPunch);
	AttackPunch->SetParam(false, deadTime, attackParam);
}

void ActionPlayerAttack::Input()
{
	//�X�e�b�v
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LSHIFT)) {
		mNextStateID = ActorStateID::ActionPlayerAvoidance;
		mNextStateFlag = true;
		return;
	}
}
