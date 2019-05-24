#include "ActionPlayScene.h"
#include "../Graphics/Graphics3D.h"
#include "../Skybox/Skybox.h"
#include "../Actor/ActionPlayerMode/ActionCamera/ActionCamera.h"
#include "../Actor/ActionPlayerMode/ActionGameManager/ActionGameManager.h"
#include "../Actor/ActionPlayerMode/UI/ActionModePause/ActionModePause.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Texture/Sprite.h"

#include "../Actor/ActionPlayerMode/ActionPlayer/ActionPlayerActor.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiActor.h"

ActionPlayScene::ActionPlayScene(){}

void ActionPlayScene::start()
{
	world_.initialize();
	GameDataManager::getInstance().initialize();


	auto P = new_actor<ActionPlayerActor>(50, 10, &world_, Vector3{ -150.0f, 30.0f,-15.0f });
	world_.add_actor(ActorGroup::Player, P);

	auto Samurai = new_actor<RedSamuraiActor>(51, 11, 12, 13, &world_, Vector3{ 0.0f, 30.0f,0.0f }, Matrix::CreateRotationY(90));
	world_.add_actor(ActorGroup::Enemy, Samurai);

	auto camera = new_actor<ActionCamera>(&world_, P);
	world_.add_actor(ActorGroup::System, camera);

	world_.add_actor(ActorGroup::System, new_actor<ActionGameManager>(&world_, P,camera));

	world_.add_actor(ActorGroup::PauseUI, new_actor<ActionModePause>(&world_));
}

void ActionPlayScene::update(float deltaTime)
{
	world_.update(deltaTime);

	if (GameDataManager::getInstance().GetPlayerDead() == true)
	{
		next_ = SceneType::SCENE_TITLE_LOAD;
		isEnd_ = true;
	}

	if (GameDataManager::getInstance().GetDeadBossEnemy() == true) {

		next_ = SceneType::SCENE_TITLE_LOAD;
		isEnd_ = true;
	}


	if (world_.GetBackTitleCheck() == true) {
		next_ = SceneType::SCENE_TITLE_LOAD;
		isEnd_ = true;
	}
}

void ActionPlayScene::draw() const
{
	Graphics3D::clear();
	//Graphics3D::clear_color(1.0f, 0.5f, 0.5f);
	//�X�J�C�{�b�N�X�̕`��
	Skybox::bind(0);
	Skybox::draw();
	//�X�e�[�W�̕`��
	CollisionMesh::bind(0);
	CollisionMesh::draw();

	world_.draw();
}

void ActionPlayScene::end()
{
	Graphics3D::finalize();
	CollisionMesh::finalize();
	Skybox::finalize();
	Sound::GetInstance().Initialize();
	Sprite::GetInstance().Initialize();
}
