#include "GameTitleScene.h"
#include "../Graphics/Graphics3D.h"
#include "../Texture/Sprite.h"
#include "../Actor/Camera/TitleSceneCamera/TitleCamera.h"
#include "../Actor/UIActor/TitleUI/TitlePlayer/TitlePlayer.h"
#include "../GameData/GameDataManager.h"

GameTitleScene::GameTitleScene()
{
}

void GameTitleScene::start()
{
	GameDataManager::getInstance().initialize();
	world_.initialize();
	auto P = new_actor<TitlePlayer>(0, 1, &world_, Vector3{ 20.0f, -35.0f,130.0f });
	world_.add_actor(ActorGroup::Player, P);

	world_.add_actor(ActorGroup::System, new_actor<TitleCamera>(&world_, P));
}

void GameTitleScene::update(float deltaTime)
{
	world_.update(deltaTime);

	if (GameDataManager::getInstance().GetTitleCheck() == true)
	{
		next_ = SceneType::SCENE_SHOOTING_PLAY_SCENE;
		isEnd_ = true;
	}
}

void GameTitleScene::draw() const
{

	//Sprite::GetInstance().DrawSetCenter(SPRITE_ID::TITLECHUI, Vector2((float)WINDOW_WIDTH / 2, WINDOW_HEIGHT/2));
	//Sprite::GetInstance().Draw(SPRITE_ID::TITLEJIKYO, Vector2(1500, 950));

	world_.draw();
}

void GameTitleScene::end()
{
}
