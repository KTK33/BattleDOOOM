#include "SelectActor.h"
#include "../Game/Define.h"
#include "../Actor/ActionPlayerMode/ActionPlayer/ActionPlayerMotionNum.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerMotionNum.h"

SelectActor::SelectActor(int model1, int model2, int weapon1, int weapon2, IWorld * world):
	Actor(world, "SelectActor", Vector3::Zero),
	mesh1{ model1 },
	mesh2{model2},
	mweapon1{weapon1},
	mweapon2{weapon2},
	mweaponPos1{103},
	mweaponPos2_{15},
	mweaponPos2_1{38}
{
	rotation_ = Matrix::CreateRotationY(180);
	mesh1.transform(Getpose());
	mesh2.transform(Getpose());
	mmotion1 = ShootingPlayerMotionNum::MotionPlayerIdle;
	mmotion2 = ActionPlayerMotion::MotionPlayerIdle;
}

void SelectActor::update(float deltaTime)
{
	mesh1.update(deltaTime);
	mesh1.transform(Getpose());
	mesh1.change_motion(mmotion1);

	mesh2.update(deltaTime);
	mesh2.transform(Getpose());
	mesh2.change_motion(mmotion2);
}

void SelectActor::draw() const
{
	if (mNum == 0)
	{
		mesh1.draw();
		mDW.draw(mweapon1, mweaponPos1, mesh1);
	}
	else if (mNum == 1)
	{
		mesh2.draw();
		mDW.draw(mweapon2, mweaponPos2_, mesh2);
		mDW.draw(mweapon2, mweaponPos2_1, mesh2);
	}

}

void SelectActor::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::SELECT_MODE_)
	{
		mNum = *(int*)param;
	}
}
