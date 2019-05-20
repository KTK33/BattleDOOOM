#include "EnemyHeadShot.h"

EnemyHeadShot::EnemyHeadShot(IWorld * world, const Vector3 & position, std::weak_ptr<Actor> ene, const IBodyPtr & body):
	Actor(world,"EnemyHead",position,body),
	m_Enemy{ene}
{}

void EnemyHeadShot::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_BALL)
	{
		if (m_Enemy.expired())return;
		m_Enemy.lock()->receiveMessage(EventMessage::HIT_BALL_HEAD,reinterpret_cast<void*>(&position_));
	}

	if (message == EventMessage::GETENEMYPOS)
	{
		position_ = *reinterpret_cast<Vector3*>(param);
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

