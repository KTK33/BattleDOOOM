#include "PlayerAttackCollision.h"

PlayerAttackCollision::PlayerAttackCollision(IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world, "AttackCollision", position, body),
	mdeadCheck{false},
	mdeadTime{ 0 },
	mattackparam{ 0 }

{}

void PlayerAttackCollision::SetParam(bool leaveCheck, int deadTime, int attackParam)
{
	mdeadCheck = leaveCheck;
	mdeadTime = deadTime;
	mattackparam = attackParam;
}

void PlayerAttackCollision::update(float deltaTime)
{
	if (mdeadCheck) return;
	mdeadTime = max(mdeadTime - 1, 0);

	if (mdeadTime <= 0)
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
	other.receiveMessage(EventMessage::HIT_PLAYER_PUNCH, (void*)&mattackparam);
}

void PlayerAttackCollision::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::GETPLAYERPOS)
	{
		position_ = *(Vector3*)param;
	}
	if (message == EventMessage::DEAD_PLAYER)
	{
		die();
	}
}
