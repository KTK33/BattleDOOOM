#include "ItemCreater.h"
#include "../Actor/ShootingPlayerMode/ItemActor/BulletItem/BulletItem.h"
#include "../Actor/ShootingPlayerMode/ItemActor/HPRecoverItem/HPRecoverItem.h"
#include "../Game/GameData/ShootingMode/ShootingPlayerData.h"

ItemCreater::ItemCreater(IWorld * world, const Vector3 & position):
	Actor(world,"ItemCreater",position)
{
	 const int ItemCreate = Random::rand(0, 100);

	if (ItemCreate <= GetItemRate)
	{
		world_->add_actor(ActorGroup::Item, std::make_shared<BulletItem>(7, world_, position_));
	}
	else 
	{
		world_->add_actor(ActorGroup::Item, std::make_shared<HPRecoverItem>(6, world_, position_));
	}
}

void ItemCreater::update(float deltaTime)
{
	die();
}
