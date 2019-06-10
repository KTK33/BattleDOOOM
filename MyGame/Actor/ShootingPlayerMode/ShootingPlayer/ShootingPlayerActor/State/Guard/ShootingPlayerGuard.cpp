#include "ShootingPlayerGuard.h"
#include "../../../ShootingPlayerMotionNum.h"
#include "../../ShootingPlayerParam/ShootingPlayerParam.h"
#include "../Input/InputInfoInc.h"

ShootingPlayerGuard::ShootingPlayerGuard(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerGuard::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerIdle;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerGuard);
	ShootingPlayerParam::getInstance().Set_WeaponModel(2);
	ShootingPlayerParam::getInstance().Set_Guard(true);
}

void ShootingPlayerGuard::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ガード解除
	if (ButtonB::GetInstance().TriggerUp())
	{
		mNextStateID = ActorStateID::ShootingPlayerIdle;
		ShootingPlayerParam::getInstance().Set_WeaponModel(1);
		ShootingPlayerParam::getInstance().Set_Guard(false);
		mNextStateFlag = true;
		return;
	}

	//アイテム使用
	if (ShootingPlayerParam::getInstance().Get_ItemUse())
	{
		mNextStateID = ActorStateID::ShootingPlayerItemUse;
		mNextStateFlag = true;
		return;
	}
}
