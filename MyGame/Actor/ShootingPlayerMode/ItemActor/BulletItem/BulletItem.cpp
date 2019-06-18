#include "BulletItem.h"
#include "../Game/GameData/ShootingMode/ShootingPlayerData.h"

BulletItem::BulletItem(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world, "BulletItem", position, body),
	mesh_{ model }
{}

void BulletItem::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
}

void BulletItem::draw() const
{
	mesh_.draw();
}

void BulletItem::onCollide(Actor & other)
{
	const Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::GET_BULLET, (void*)&GetBulletPoint);
}

void BulletItem::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_PLAYER)
	{
		die();
	}
}
