#include "EnemyAttack.h"

EnemyAttack::EnemyAttack(IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world,"EnemyAttack",position,body),
	deadTime{0},
	attackparam{0}
{
}

void EnemyAttack::initialize()
{
}

void EnemyAttack::SetdeadTime(int time)
{
	deadTime = time;
}

void EnemyAttack::SetAttackParam(int param)
{
	attackparam = param;
}

void EnemyAttack::update(float deltaTime)
{
	deadTime = max(deadTime - 1, 0);

	if (deadTime <= 0)
	{
		die();
	}
}

void EnemyAttack::draw() const
{
	body_->transform(Getpose())->draw();
}

void EnemyAttack::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY_BULLET, (void*)&attackparam);
}

void EnemyAttack::receiveMessage(EventMessage message, void * param)
{
}
