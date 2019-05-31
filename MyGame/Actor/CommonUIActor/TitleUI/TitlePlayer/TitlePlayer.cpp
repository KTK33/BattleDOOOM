#include "TitlePlayer.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerMotionNum.h"
#include "../Actor/CommonUIActor/TitleUI/TitleBullet/TitleBullet.h"

TitlePlayer::TitlePlayer(int model, int weapon, IWorld * world, const Vector3 & position):
	Actor(world,"TitlePlayer",position),
	mesh_{model},
	mweapon_{weapon},
	mTimer{ 0 }
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());

	ActorSystem::TransparenceInit();

	mmotion_ = ShootingPlayerMotionNum::MotionPlayerIdleAiming;
}

void TitlePlayer::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(mmotion_);

	mTimer = min(mTimer + 1, 31);

	if (mTimer == 30)
	{
		world_->add_actor(ActorGroup::Ball, new_actor<TitleBullet>(5, world_, Vector3{ position_.x,position_.y + 14.0f,position_.z} +rotation_.Forward() * 4.5f + rotation_.Right() *1.4f,rotation_.Forward()));
	}
}

void TitlePlayer::draw() const
{
	mesh_.draw();
	mDW.draw(mweapon_, 103, mesh_);
}