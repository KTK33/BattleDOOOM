#include "EnemyAttackCollison.h"

EnemyAttackCollison::EnemyAttackCollison(IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world,"EnemyAttackCollison",position,body),
	deadTime{0},
	attackparam{0}
{
}

void EnemyAttackCollison::initialize()
{
}

void EnemyAttackCollison::SetdeadTime(int time)
{
	deadTime = time;
}

void EnemyAttackCollison::SetAttackParam(int param)
{
	attackparam = param;
}

void EnemyAttackCollison::update(float deltaTime)
{
	deadTime = max(deadTime - 1, 0);

	if (deadTime <= 0)
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
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY_BULLET, (void*)&attackparam);
}

void EnemyAttackCollison::receiveMessage(EventMessage message, void * param)
{
}
