#include "GameClearUIh.h"
#include "../../../Texture/Sprite.h"

GameClearUI::GameClearUI(IWorld * world):
	Actor(world,"GameClearUI",Vector3::Zero)
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
	Sprite::GetInstance().Draw(SPRITE_ID::GAMEOVERBACK, Vector2(0, 0));

	Vector2 NameSize = Sprite::GetInstance().GetSize(SPRITE_ID::GAMEOVERNAME);
	Sprite::GetInstance().Draw(SPRITE_ID::GAMEOVERNAME, Vector2((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT - 900), NameSize / 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
