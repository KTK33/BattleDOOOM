#include "PlayerPunchAttack.h"

PlayerPunchAttack::PlayerPunchAttack(IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world, "PlayerPunchAttack", position, body),
	deadTime{ 0 },
	attackparam{ 0 }

{
}

void PlayerPunchAttack::initialize()
{
}

void PlayerPunchAttack::SetdeadTime(int time)
{
	deadTime = time;
}

void PlayerPunchAttack::SetAttackParam(int param)
{
	attackparam = param;
}

void PlayerPunchAttack::update(float deltaTime)
{
	deadTime = max(deadTime - 1, 0);

	if (deadTime <= 0)
	{
		die();
	}
}

void PlayerPunchAttack::draw() const
{
	body_->transform(Getpose())->draw();
}

void PlayerPunchAttack::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER_PUNCH, (void*)&attackparam);
}

void PlayerPunchAttack::receiveMessage(EventMessage message, void * param)
{
}
