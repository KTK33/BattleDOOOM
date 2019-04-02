#include "GameClearUIh.h"
#include "../../../Texture/Sprite.h"

GameClearUI::GameClearUI(IWorld * world):
	Actor(world,"GameClearUI",Vector3::Zero),
	GameClearBackAlpha{0}
{
}

void GameClearUI::initialize()
{
}

void GameClearUI::update(float deltaTime)
{
	GameClearBackAlpha = min(GameClearBackAlpha + 1, 225);
}

void GameClearUI::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, GameClearBackAlpha);
	Sprite::GetInstance().Draw(SPRITE_ID::GAMECLEARBACK, Vector2(0, 0));

	Vector2 NameSize = Sprite::GetInstance().GetSize(SPRITE_ID::GAMECLEARNAME);
	Sprite::GetInstance().Draw(SPRITE_ID::GAMECLEARNAME, Vector2((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT - 900), NameSize / 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
