#include "ActionModeManager.h"
#include "../Actor/CommonUIActor/FadeUI/FadeUI.h"
#include "../Actor/ActionPlayerMode/ActionPlayer/ActionPlayerActor.h"
#include "../Actor/ActionPlayerMode/ActionCamera/ActionCamera.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiActor.h"
#include "../Actor/ActionPlayerMode/ActionCamera/TargetCameraManager.h"
#include "../Actor/ActionPlayerMode/UI/ActionModePause/ActionModePause.h"

ActionModeManager::ActionModeManager(IWorld * world):
	Actor(world, "ActionModeManager", Vector3::Zero)
{
	initialize();
}

void ActionModeManager::initialize()
{
	world_->add_actor(ActorGroup::Fade, new_actor<FadeUI>(world_, 1, 0));

	auto P = new_actor<ActionPlayerActor>(50, 10, world_, Vector3{ -150.0f, 30.0f,0.0f }, Matrix::CreateRotationY(-90));
	world_->add_actor(ActorGroup::Player, P);

	auto Samurai = new_actor<RedSamuraiActor>(51, 14, 12, 13, world_, Vector3{ 0.0f, 30.0f,0.0f }, Matrix::CreateRotationY(90));
	world_->add_actor(ActorGroup::Enemy, Samurai);

	auto camera = new_actor<ActionCamera>(world_, P);
	world_->add_camera(camera);

	world_->add_actor(ActorGroup::System, new_actor<TargetCameraManager>(world_, P, camera));

	world_->add_actor(ActorGroup::PauseUI, new_actor<ActionModePause>(world_));
}

void ActionModeManager::update(float deltaTime)
{}

void ActionModeManager::draw() const
{}
