#include "RedSamuraiHP.h"
#include "../Texture/Sprite.h"
#include "../Game/Define.h"

void RedSamuraiHP::draw(int hp) const
{
	//HP
	Sprite::GetInstance().Draw(SPRITE_ID::REDSAMURAI_HPFRAME, Vector2(100, Sprite::GetInstance().GetSize(SPRITE_ID::REDSAMURAI_HPFRAME).y));
	Sprite::GetInstance().DrawPart(SPRITE_ID::REDSAMURAI_HPGAUGE, Vector2(100, Sprite::GetInstance().GetSize(SPRITE_ID::REDSAMURAI_HPFRAME).y), 0, 0,
		static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::REDSAMURAI_HPGAUGE).x / PlayerHP * hp), static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::REDSAMURAI_HPGAUGE).y));
}
