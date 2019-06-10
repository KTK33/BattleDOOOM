#include "TestScene.h"
#include <EffekseerForDXLib.h>
#include "../Actor/Camera/TPSCamera.h"

#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/ShootingPlayerActor.h"
#include "../Actor/ShootingPlayerMode/UIActor/ShootingPlayerTextUI/ShootingPlayerTextUI.h"

#include "../Effekseer/EFFECT_ID.h"

TestScene::TestScene():
	eff_{(int)EFFECT_ID::PLAYER_HEAL}
{
}

void TestScene::start()
{
	world_.initialize();

	auto P_Text = new_actor<ShootingPlayerTextUI>(&world_);
	world_.add_actor(ActorGroup::UI, P_Text);

	auto P = new_actor<ShootingPlayerActor>(0, 1, &world_, Vector3{ 0.0f, 0.0f,0.0f }, P_Text);
	world_.add_actor(ActorGroup::Player, P);

	eff_.play();
}

void TestScene::update(float deltaTime)
{
	world_.update(deltaTime);

	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(Vector3(100,100,100));
	TPSCamera::GetInstance().Target.Set(Vector3(0,0,0));
	TPSCamera::GetInstance().Up.Set(Vector3::Up);
	TPSCamera::GetInstance().Update();

	//eff_.set_scale(Vector3{ 1.0f,1.0f,1.0f });
	//eff_.set_rotation(0.0f, 0.0f, 0.0f);
	//eff_.set_position(Vector3(30,10,30));

	eff_.update(1.0f);
}

void TestScene::draw() const
{
	Graphics3D::clear();
	world_.draw();

	eff_.draw();

	Effekseer_Sync3DSetting();
}

void TestScene::end()
{
	Graphics3D::finalize();
	CollisionMesh::finalize();
	Skybox::finalize();
	Sound::GetInstance().Initialize();
	Sprite::GetInstance().Initialize();
}
