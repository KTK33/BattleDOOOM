#include "GameTitleScene.h"
#include "../Graphics/Graphics3D.h"
#include "../Texture/Sprite.h"

GameTitleScene::GameTitleScene()
{
}

void GameTitleScene::start()
{
}

void GameTitleScene::update(float deltaTime)
{
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2))
	{
		next_ = SceneType::SCENE_GAMEPLAY;
		isEnd_ = true;
	}
}

void GameTitleScene::draw() const
{
	Graphics3D::clear_color(255, 255, 255);

	SetBackgroundColor(96, 96, 200);

	Sprite::GetInstance().DrawSetCenter(SPRITE_ID::TITLENAME, Vector2((float)WINDOW_WIDTH / 2, 800));

}

void GameTitleScene::end()
{
}
