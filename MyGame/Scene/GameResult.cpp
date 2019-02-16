#include "GameResult.h"
#include "../Graphics/Graphics3D.h"

GameResultScene::GameResultScene()
{
}

void GameResultScene::start()
{
}

void GameResultScene::update(float deltaTime)
{
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
	{
		next_ = SceneType::SCENE_TITLE;
		isEnd_ = true;
	}
}

void GameResultScene::draw() const
{
	Graphics3D::clear_color(255, 255, 255);

	SetFontSize(128);
	DrawFormatString(100, 500, GetColor(255, 255, 255), "ÉQÅ[ÉÄÉäÉUÉãÉg");
	SetFontSize(16);
	SetBackgroundColor(96, 96, 200);
}

void GameResultScene::end()
{
}
