#include "EnemyAttackCollison.h"

EnemyAttackCollison::EnemyAttackCollison(IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world,"EnemyAttackCollison",position,body),
	mdeadCheck{false},
	mdeadTime{0},
	mattackparam{0}
{}

void EnemyAttackCollison::SetParam(bool deadCheck, int deadTime, int attackParam)
{
	mdeadCheck = deadCheck;
	mdeadTime = deadTime;
	mattackparam = attackParam;
}

void EnemyAttackCollison::update(float deltaTime)
{
	if (mdeadCheck) return;
	mdeadTime = max(mdeadTime - 1, 0);

	if (mdeadTime <= 0)
	{
		die();
	}
}

void EnemyAttackCollison::draw() const
{
	body_->transform(Getpose())->draw();
}

void EnemyAttackCollison::onCollide(Actor & other)
{
	const Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY_BULLET, (void*)&mattackparam);
}

void EnemyAttackCollison::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_PLAYER)
	{
		die();
	}
}
