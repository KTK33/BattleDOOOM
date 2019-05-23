#include "GameTitleScene.h"
#include "../Graphics/Graphics3D.h"
#include "../Texture/Sprite.h"
#include "../Actor/Camera/TitleSceneCamera/TitleCamera.h"
#include "../Actor/CommonUIActor/TitleUI/TitlePlayer/TitlePlayer.h"
#include "../GameData/GameDataManager.h"
#include "../Sound/Sound.h"

GameTitleScene::GameTitleScene()
{
}

void GameTitleScene::start()
{
	GameDataManager::getInstance().initialize();
	world_.initialize();
	Sound::GetInstance().StopBGM();
	auto P = new_actor<TitlePlayer>(0, 1, &world_, Vector3{ 20.0f, -35.0f,130.0f });
	world_.add_actor(ActorGroup::Player, P);

	world_.add_actor(ActorGroup::System, new_actor<TitleCamera>(&world_, P));

}

void GameTitleScene::update(float deltaTime)
{
	world_.update(deltaTime);

	if (GameDataManager::getInstance().GetTitleCheck() == true)
	{
		next_ = SceneType::SCENE_MODESELECT;
		isEnd_ = true;
	}
}

void GameTitleScene::draw() const
{
	Graphics3D::clear_color(0, 0, 0);
	world_.draw();
}

void GameTitleScene::end()
{
}
