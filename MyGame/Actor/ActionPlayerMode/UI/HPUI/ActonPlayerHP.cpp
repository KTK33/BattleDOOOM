#include "ActonPlayerHP.h"
#include "../Texture/Sprite.h"
#include "../Game/Define.h"

void ActionPlayerHP::draw(int hp) const
{
	//HP
	Sprite::GetInstance().Draw(SPRITE_ID::ACTION_PLAYER_HPFRAME, Vector2(100, WINDOW_HEIGHT - Sprite::GetInstance().GetSize(SPRITE_ID::ACTION_PLAYER_HPFRAME).y - 100));
	Sprite::GetInstance().DrawPart(SPRITE_ID::ACTION_PLAYER_HPGAUGE, Vector2(100, WINDOW_HEIGHT - Sprite::GetInstance().GetSize(SPRITE_ID::ACTION_PLAYER_HPGAUGE).y - 100), 0, 0,
		static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::ACTION_PLAYER_HPGAUGE).x / PlayerHP * hp), static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::ACTION_PLAYER_HPGAUGE).y));
}
