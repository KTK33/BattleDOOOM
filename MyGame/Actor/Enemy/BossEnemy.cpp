#include "BossEnemy.h"

BossEnemy::BossEnemy(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body) :
	Actor(world, "BossEnemy", position, body),
	mesh_(model)
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());

	hp_ = 10;
}

void BossEnemy::initialize()
{
}

void BossEnemy::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());

	if (hp_ <= 0)
	{
		deadAction();
	}

}

void BossEnemy::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}

void BossEnemy::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (void*)&hitdir);
}

void BossEnemy::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_BALL){
		hp_ -= 1;
	}
}

void BossEnemy::hit_player(const Vector3 & dir)
{
}

void BossEnemy::deadAction()
{
	die();
}
