#include "ShootingModeManager.h"
#include "../Actor/CommonUIActor/FadeUI/FadeUI.h"
#include "../Actor/ShootingPlayerMode/UIActor/ShootingPlayerTextUI/ShootingPlayerTextUI.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/ShootingPlayerActor.h"
#include "../Actor/ShootingPlayerMode/UIActor/AnyUI/AnyUI.h"
#include "../Actor/ShootingPlayerMode/UIActor/Pause/Pause.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/NormalEnemy/NormalEnemyActor.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BossEnemy/BossEnemyActor.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BigBossEnemy/BigBossEnemyActor.h"
#include "../Actor/ShootingPlayerMode/ShootingCamera/ShootingCamera.h"

ShootingModeManager::ShootingModeManager(IWorld * world):
	Actor(world, "ShootingModeManager", Vector3::Zero),
	BossArleady{ false }
{
	initialize();
}

void ShootingModeManager::initialize()
{
	world_->add_actor(ActorGroup::Fade, new_actor<FadeUI>(world_, 1, 0));

	auto P_Text = new_actor<ShootingPlayerTextUI>(world_);
	world_->add_actor(ActorGroup::UI, P_Text);

	auto P = new_actor<ShootingPlayerActor>(0, 1, world_, Vector3{ 0.0f, 30.0f,0.0f }, P_Text);
	world_->add_actor(ActorGroup::Player, P);

	auto ANYUI = new_actor<AnyUI>(world_);
	world_->add_actor(ActorGroup::UI, ANYUI);

	world_->add_actor(ActorGroup::PauseUI, new_actor<PauseUI>(world_));

	auto dummy1 = new_actor<NormalEnemyActor>(11, world_, Vector3{ 20.0f, 30.0f,  -150.0f }, Matrix::CreateRotationY(Random::rand(0.0f, 360.0f)));
	world_->add_actor(ActorGroup::Enemy, dummy1);

	auto dummy2 = new_actor<NormalEnemyActor>(12, world_, Vector3{ 130.0f, 30.0f, -4.0f }, Matrix::CreateRotationY(Random::rand(0.0f, 360.0f)));
	world_->add_actor(ActorGroup::Enemy, dummy2);

	auto dummy3 = new_actor<NormalEnemyActor>(13, world_, Vector3{ -110.0f , 30.0f, 90.0f }, Matrix::CreateRotationY(Random::rand(0.0f, 360.0f)));
	world_->add_actor(ActorGroup::Enemy, dummy3);


	//world_->add_actor(ActorGroup::BigBossEnemy, new_actor<BigBossEnemyActor>(9, world_, Vector3{ 200.0f, 300.0f,20.0f }));

	world_->add_camera(new_actor<ShootingCamera>(world_, P));
}

void ShootingModeManager::update(float deltaTime)
{
	if (world_->find_actor(ActorGroup::Enemy, "NormalEnemy") == NULL && BossArleady == false)
	{
		world_->add_actor(ActorGroup::BossEnemy, new_actor<BossEnemyActor>(3, world_, Vector3{ 0.0f, 30.0f,0.0f }));
		BossArleady = true;
	}
}

void ShootingModeManager::draw() const
{
}
