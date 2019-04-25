#include "PlayerGunAttack.h"

PlayerGunAttack::PlayerGunAttack(IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world, "PlayerPunchAttack", position, body),
	deadTime{ 0 },
	attackparam{ 0 }

{
}

void PlayerGunAttack::initialize()
{
}

void PlayerGunAttack::SetdeadTime(int time)
{
	deadTime = time;
}

void PlayerGunAttack::SetAttackParam(int param)
{
	attackparam = param;
}

void PlayerGunAttack::update(float deltaTime)
{
	deadTime = max(deadTime - 1, 0);

	if (deadTime <= 0)
	{
		die();
	}
}

void PlayerGunAttack::draw() const
{
	body_->transform(Getpose())->draw();
}

void PlayerGunAttack::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER_PUNCH, (void*)&attackparam);
}

void PlayerGunAttack::receiveMessage(EventMessage message, void * param)
{
}
