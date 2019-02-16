#include "ItemCreater.h"
#include "BulletItem.h"
#include "HPRecoverItem.h"

ItemCreater::ItemCreater(IWorld * world, const Vector3 & position):
	Actor(world,"ItemCreater",position)
{
}

void ItemCreater::initialize()
{
}

void ItemCreater::update(float deltaTime)
{
	int ItemCreate = Random::rand(0, 1);
	switch (ItemCreate)
	{
	case 0:
		world_->add_actor(ActorGroup::Item, std::make_shared<BulletItem>(2, world_, position_));
		break;
	default:
		world_->add_actor(ActorGroup::Item, std::make_shared<HPRecoverItem>(2, world_, position_));
		break;
	}
	die();
}

void ItemCreater::receiveMessage(EventMessage message, void * param)
{
}
