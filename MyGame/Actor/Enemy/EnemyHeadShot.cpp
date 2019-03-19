#include "EnemyHeadShot.h"

EnemyHeadShot::EnemyHeadShot(IWorld * world, const Vector3 & position, std::weak_ptr<Actor> ene, const IBodyPtr & body):
	Actor(world,"EnemyHead",position,body),
	m_Enemy{ene}
{
}

void EnemyHeadShot::initialize()
{
}

void EnemyHeadShot::update(float deltaTime)
{
}

void EnemyHeadShot::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_BALL)
	{
		m_Enemy.lock()->receiveMessage(EventMessage::HIT_BALL_HEAD,(void*)&position_);
	}

	if (message == EventMessage::GETENEMYPOS)
	{
		position_ = *(Vector3*)param;
	}
	if (message == EventMessage::DEAD_DUMMY_ENEMY)
	{
		die();
	}
}

void EnemyHeadShot::draw() const
{
	body_->transform(Getpose())->draw();
}

void EnemyHeadShot::onCollide(Actor & other)
{
	other.receiveMessage(EventMessage::HIT_ENEMY, nullptr);
}

