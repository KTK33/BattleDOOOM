#include "GameOverUI.h"
#include "../../../Texture/Sprite.h"

GameOverUI::GameOverUI(IWorld * world):
	Actor(world,"GameOverBack",Vector3::Zero),
	GameOverBackAlpha{0}
{
}

void GameOverUI::initialize()
{
}

void GameOverUI::update(float deltaTime)
{
	GameOverBackAlpha = min(GameOverBackAlpha + 1, 225);
}

void GameOverUI::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, GameOverBackAlpha);
	Sprite::GetInstance().Draw(SPRITE_ID::GAMEOVERBACK, Vector2(0,0));

	Vector2 NameSize = Sprite::GetInstance().GetSize(SPRITE_ID::GAMEOVERNAME);
	Sprite::GetInstance().Draw(SPRITE_ID::GAMEOVERNAME, Vector2((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT - 900), NameSize/2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
