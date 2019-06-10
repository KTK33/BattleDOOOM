#include "NormalEnemyRoar.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/NormalEnemy/NormalEnemyMotionNum.h"

NormalEnemyRoar::NormalEnemyRoar(IWorld * world, ActorParameters & parameter):
	meff{(int)EFFECT_ID::ENEMY_ROAR}
{
	world_ = world;
	parameters_ = &parameter;
}

void NormalEnemyRoar::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::NormalEnemyDamage;
	parameters_->Set_Motion(NormalEnemyMotionNum::MotionNormalEnemyRoar);

	meff.set_endTime(150);
	meff.play();
}

void NormalEnemyRoar::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	meff.set_position(Vector3(lposition.x, lposition.y + 15.0f, lposition.z));
	meff.set_scale(Vector3(5.0f, 5.0f, 5.0f));
	Matrix angle = Matrix::Invert(lrotation);
	meff.set_rotation(Vector3(0, Matrix::Angle(angle).y, 0));
	meff.update(0.5f);

	meff.draw();

	//ƒ‚[ƒVƒ‡ƒ“‚ÌŽžŠÔ‚ªI‚í‚Á‚½‚ç
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::NormalEnemyIdle;
		parameters_->Set_Invicibly(false);
		mNextStateFlag = true;
		return;
	}
}
