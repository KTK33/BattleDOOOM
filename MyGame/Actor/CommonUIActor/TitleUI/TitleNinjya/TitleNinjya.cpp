#include "TitleNinjya.h"
#include "../Actor/ActionPlayerMode/ActionPlayer/ActionPlayerMotionNum.h"

TitleNinjya::TitleNinjya(int model, int weapon, IWorld * world, const Vector3 & position):
	Actor(world, "TitleNinjya", position),
	mesh_{ model },
	mweapon_{ weapon }
{
	rotation_ = Matrix::CreateRotationY(180);
	mesh_.transform(Getpose());

	mmotion_ = ActionPlayerMotion::MotionPlayerRun;
}

void TitleNinjya::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(mmotion_);

	position_ += rotation_.Forward() * 0.3f;
}

void TitleNinjya::draw() const
{
	mesh_.draw();
	mDW.draw(mweapon_, 15, mesh_);
	mDW.draw(mweapon_, 38, mesh_);
}
