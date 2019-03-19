#include "TitleBullet.h"
#include "../Effect.h"
#include "TitleAnyUI.h"

TitleBullet::TitleBullet(int model, IWorld * world, const Vector3 & position,Vector3 move):
	Actor(world,"TitleBullet",position),
	mesh_{model},
	MovePos{move},
	Timer{0}
{
}

void TitleBullet::initialize()
{
}

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
		world_->add_actor(ActorGroup::Effect, new_actor<Effect>(world_, position_,4.0f, SPRITE_ID::EFFECT_BULLETHIT));
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
