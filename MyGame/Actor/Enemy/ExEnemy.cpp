#include "ExEnemy.h"

ExEnemy::ExEnemy(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world,"ExEnemy",position,body),
	mesh_{model}
{
	rotation_ *= Matrix::CreateRotationY(180.0f);
	mesh_.transform(Getpose());
}

void ExEnemy::initialize()
{

}

void ExEnemy::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());

}

void ExEnemy::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}

void ExEnemy::onCollide(Actor & other)
{
}

void ExEnemy::receiveMessage(EventMessage message, void * param)
{
}

void ExEnemy::update_state(float deltaTime)
{
}

void ExEnemy::Idle()
{
}

void ExEnemy::MoveWalk()
{
}

void ExEnemy::MoveRun()
{
}

void ExEnemy::Punch()
{
}

void ExEnemy::Damage()
{
}

void ExEnemy::Dead()
{
}

void ExEnemy::change_state(ExEnemyState::State state, int motion)
{
}

void ExEnemy::hit_player(const Vector3 & dir)
{
}

void ExEnemy::deadAction()
{
}

void ExEnemy::Delay()
{
}
