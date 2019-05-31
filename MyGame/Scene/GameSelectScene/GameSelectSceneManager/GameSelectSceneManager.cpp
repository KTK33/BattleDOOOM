#include "GameSelectSceneManager.h"
#include "../Actor/CommonUIActor/SelectActor/SelectActor.h"
#include "../Actor/Camera/SelectCamera/SelectCamera.h"

GameSelectSceneManager::GameSelectSceneManager(IWorld * world):
Actor(world, "SelectSceneManager", Vector3::Zero)
{
	initialize();
}

void GameSelectSceneManager::initialize()
{
	auto P = new_actor<SelectActor>(0, 50, 1, 10, world_);
	world_->add_actor(ActorGroup::Player, P);

	world_->add_actor(ActorGroup::System, new_actor<SelectCamera>(world_, P));
}

void GameSelectSceneManager::update(float deltaTime)
{}

void GameSelectSceneManager::draw() const
{}
