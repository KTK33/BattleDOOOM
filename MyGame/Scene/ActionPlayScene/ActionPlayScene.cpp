#include "ActionPlayScene.h"
#include "../Graphics/Graphics3D.h"
#include "../Actor/Player/Player.h"
#include "../Actor/UIActor/PlayerTextUI.h"
#include "../Actor/Camera/ActionCamera/ActionCamera.h"

ActionPlayScene::ActionPlayScene()
{
}

void ActionPlayScene::start()
{
	world_.initialize();

	auto P_Text = new_actor<PlayerTextUI>(&world_);
	world_.add_actor(ActorGroup::UI, P_Text);

	auto P = new_actor<Player>(0, 1, &world_, Vector3{ 0.0f, -20.0f,0.0f }, P_Text);
	world_.add_actor(ActorGroup::Player, P);

	world_.add_actor(ActorGroup::System, new_actor<ActionCamera>(&world_, P));

}

void ActionPlayScene::update(float deltaTime)
{
	world_.update(deltaTime);
}

void ActionPlayScene::draw() const
{
	Graphics3D::clear();
	//Graphics3D::clear_color(1.0f, 0.5f, 0.5f);
	//スカイボックスの描画
	Skybox::bind(0);
	Skybox::draw();
	//ステージの描画
	CollisionMesh::bind(0);
	CollisionMesh::draw();

	world_.draw();
}

void ActionPlayScene::end()
{
}
