#include "GameOverScene.h"
#include "../Graphics/Graphics3D.h"
#include "../Input/GamePad/GamePad.h"

GameOrverScene::GameOrverScene()
{
}

void GameOrverScene::start()
{
}

void GameOrverScene::update(float deltaTime)
{
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2))
	{
		next_ = SceneType::SCENE_TITLE;
		isEnd_ = true;
	}
}

void GameOrverScene::draw() const
{
	Graphics3D::clear_color(255, 255, 255);

	SetFontSize(128);
	DrawFormatString(100, 500, GetColor(255, 255, 255), "ゲームオーバー");
	SetFontSize(16);
	SetBackgroundColor(96, 96, 200);
}

void GameOrverScene::end()
{
}
