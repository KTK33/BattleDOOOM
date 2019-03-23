#include "PlayerAdvent.h"
#include "../../Scene/GameData/GameDataManager.h"

PlayerAdvent::PlayerAdvent(IWorld * world):
	Actor(world,"PlayerAdvent",Vector3::Zero),
	count{0}
{
}

void PlayerAdvent::initialize()
{
}

void PlayerAdvent::update(float deltaTime)
{
	count++;
	if (count >= 200)
	{
		GameDataManager::getInstance().SetPlayerStart(true);
		die();
	}
}

void PlayerAdvent::receiveMessage(EventMessage message, void * param)
{
}

void PlayerAdvent::draw() const
{
}
