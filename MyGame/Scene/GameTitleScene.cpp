#include "GameTitleScene.h"
#include "../Graphics/Graphics3D.h"

GameTitleScene::GameTitleScene()
{
}

void GameTitleScene::start()
{
}

void GameTitleScene::update(float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		next_ = SceneType::SCENE_GAMEPLAY;
		isEnd_ = true;
	}
}

void GameTitleScene::draw() const
{
	Graphics3D::clear_color(255, 255, 255);

	SetBackgroundColor(96, 96, 200);
}

void GameTitleScene::end()
{
}
