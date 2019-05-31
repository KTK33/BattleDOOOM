#include "TitleBullet.h"
#include "../Actor/CommonUIActor/Effect2D/Effect2D.h"
#include "../Actor/CommonUIActor/TitleUI/TitleAnyUI/TitleAnyUI.h"
#include "../Sound/Sound.h"
#include "../Actor/CommonUIActor/TitleUI/TitleNinjya/TitleNinjya.h"

TitleBullet::TitleBullet(int model, IWorld * world, const Vector3 & position,Vector3 move):
	Actor(world,"TitleBullet",position),
	mesh_{model},
	MovePos{move},
	Timer{0}
{}

void TitleBullet::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());


	Timer++;
	if (Timer <= 150)
	{
		position_ += MovePos / 10;
	}

	if (Timer == 150)
	{
		world_->add_actor(ActorGroup::Effect, new_actor<Effect2D>(world_, position_,8.0f, SPRITE_ID::EFFECT_BULLETHIT));
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DAMAGEENEMY_SE);
	}

	if (Timer == 160)
	{
		Vector3 ninjyaPos = Vector3(position_.x + 5.0f, position_.y - 10.0f, position_.z);
		world_->add_actor(ActorGroup::TitleActor, new_actor<TitleNinjya>(50, 10, world_, ninjyaPos + rotation_.Forward() * 20));
	}

	if (Timer > 150)
	{
		if (world_->find_actor(ActorGroup::Effect, "Effect") == NULL)
		{
			world_->add_actor(ActorGroup::UI, new_actor<TitleAnyUI>(world_));
			die();
		}
	}
}

void TitleBullet::draw() const
{
	if (Timer <= 150)
	{
		mesh_.draw();
	}
}
