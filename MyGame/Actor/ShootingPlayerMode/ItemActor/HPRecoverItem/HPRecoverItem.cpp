#include "HPRecoverItem.h"

HPRecoverItem::HPRecoverItem(int model,IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world,"HPRecoverItem",position,body),
	mesh_{model}
{
}

void HPRecoverItem::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
}

void HPRecoverItem::draw() const
{
	mesh_.draw();
	//body_->transform(Getpose())->draw();
}

void HPRecoverItem::onCollide(Actor & other)
{
	const Vector3 hitdir(other.Getposition() - position_);
	int hppoint = 3;
	other.receiveMessage(EventMessage::GET_HPRECOVER, (void*)&hppoint);
}

void HPRecoverItem::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_PLAYER)
	{
		die();
	}
}
