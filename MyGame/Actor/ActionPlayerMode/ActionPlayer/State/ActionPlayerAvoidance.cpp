#include "ActionPlayerAvoidance.h"
#include "../Actor/ActionPlayerMode/ActionPlayer/ActionPlayerMotionNum.h"
#include "../Input/InputInfoInc.h"

ActionPlayerAvoidance::ActionPlayerAvoidance(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ActionPlayerAvoidance::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerAvoidance;

	parameters_->Set_Motion(ActionPlayerMotion::MotionPlayerAvoidance);
}

void ActionPlayerAvoidance::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//入力情報
	Input();
	//モーションの時間が終わったら移動状態へ
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::ActionPlayerIdel;
		mNextStateFlag = true;
		return;
	}
	//HPが０になったら死亡
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::ActionPlayerDead;
		mNextStateFlag = true;
		return;
	}
}

void ActionPlayerAvoidance::Input()
{
	//ステップ派生攻撃
	if(ButtonB::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ActionPlayerAvoidanceAttack;
		mNextStateFlag = true;
		return;
	}
	//ステップ
	if(ButtonA::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ActionPlayerAvoidance;
		mNextStateFlag = true;
		return;
	}
}
