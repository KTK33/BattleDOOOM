#include "TitlePlayer.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerMotionNum.h"
#include "../Actor/CommonUIActor/TitleUI/TitleBullet/TitleBullet.h"

TitlePlayer::TitlePlayer(int model, int weapon, IWorld * world, const Vector3 & position):
	Actor(world,"TitlePlayer",position),
	mesh_{model},
	weapon_{weapon},
	Timer{ 0 }
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());

	ActorSystem::TransparenceInit();

	motion_ = ShootingPlayerMotionNum::MotionPlayerIdleAiming;
}

void TitlePlayer::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(motion_);

	Timer = min(Timer + 1, 31);

	if (Timer == 30)
	{
		//motion_ = PlayerMotion::Motion::motion;
		world_->add_actor(ActorGroup::Ball, new_actor<TitleBullet>(5, world_, Vector3{ position_.x,position_.y + 14.0f,position_.z} +rotation_.Forward() * 4.5f + rotation_.Right() *1.4f,rotation_.Forward()));
	}
}

void TitlePlayer::draw() const
{
	mesh_.draw();
	draw_weapon();
}

void TitlePlayer::draw_weapon() const
{
	StaticMesh::bind(weapon_);
	StaticMesh::transform(mesh_.bone_matrix(103));
	StaticMesh::draw();
}
