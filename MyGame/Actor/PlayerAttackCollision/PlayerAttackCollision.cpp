#include "PlayerAttackCollision.h"

PlayerAttackCollision::PlayerAttackCollision(IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world, "AttackCollision", position, body),
	deadTime{ 0 },
	attackparam{ 0 }

{
}

void PlayerAttackCollision::initialize()
{
}

void PlayerAttackCollision::SetdeadTime(int time)
{
	deadTime = time;
}

void PlayerAttackCollision::SetAttackParam(int param)
{
	attackparam = param;
}

void PlayerAttackCollision::update(float deltaTime)
{
	deadTime = max(deadTime - 1, 0);

	if (deadTime <= 0)
	{
		die();
	}
}

void PlayerAttackCollision::draw() const
{
	body_->transform(Getpose())->draw();
}

void PlayerAttackCollision::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER_PUNCH, (void*)&attackparam);
}

void PlayerAttackCollision::receiveMessage(EventMessage message, void * param)
{
}
