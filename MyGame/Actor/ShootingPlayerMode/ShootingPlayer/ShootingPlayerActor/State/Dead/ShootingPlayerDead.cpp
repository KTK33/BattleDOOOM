#include "ShootingPlayerDead.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"
#include "../Scene/GameData/GameDataManager.h"

ShootingPlayerDead::ShootingPlayerDead(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerDead::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerDead;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerDead);

	GameDataManager::getInstance().SetPlayerDead(true);

	ShootingPlayerParam::getInstance().Set_AimCheck(false);
}

void ShootingPlayerDead::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_IsDead(true);
		return;
	}

}