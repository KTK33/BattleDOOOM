#include "EnemyAttackFire.h"

EnemyAttackFire::EnemyAttackFire(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world,"EnemyAttackFire",position,body),
	mesh_{model},
	EnemyForward{Vector3::Zero}
{
	mesh_.transform(Getpose());
}

void EnemyAttackFire::initialize()
{
}

void EnemyAttackFire::update(float deltaTime)
{
	mesh_.update(deltaTime);
	//s—ñ‚ÌÝ’è
	mesh_.transform(Getpose());

	position_ += EnemyForward;

	DeadTimer++;
	if (DeadTimer >= 60) die();
}

void EnemyAttackFire::onCollide(Actor & other)
{
	int DamageVal = 2;
	other.receiveMessage(EventMessage::HIT_ENEMY_BULLET, (void*)&DamageVal);
}

void EnemyAttackFire::receiveMessage(EventMessage message, void * param)
{
}

void EnemyAttackFire::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}

void EnemyAttackFire::GetEnemyForward(Vector3 forward)
{
	EnemyForward = forward;
}
