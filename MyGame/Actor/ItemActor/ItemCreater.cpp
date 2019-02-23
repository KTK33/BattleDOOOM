#include "ItemCreater.h"
#include "BulletItem.h"
#include "HPRecoverItem.h"

ItemCreater::ItemCreater(IWorld * world, const Vector3 & position):
	Actor(world,"ItemCreater",position)
{
	int ItemCreate = Random::rand(0, 3);
	//switch (ItemCreate)
	//{
	//case 0:
	//	world_->add_actor(ActorGroup::Item, std::make_shared<BulletItem>(7, world_, position_));
	//	break;
	//case 1:
	//	world_->add_actor(ActorGroup::Item, std::make_shared<HPRecoverItem>(6, world_, position_));
	//	break;
	//default:
	//	break;
	//}

	if (ItemCreate == 3) {
		world_->add_actor(ActorGroup::Item, std::make_shared<HPRecoverItem>(6, world_, position_));
	}
	else {
		world_->add_actor(ActorGroup::Item, std::make_shared<BulletItem>(7, world_, position_));
	}
}

void ItemCreater::initialize()
{
}

void ItemCreater::update(float deltaTime)
{
	die();
}

void ItemCreater::receiveMessage(EventMessage message, void * param)
{
}
