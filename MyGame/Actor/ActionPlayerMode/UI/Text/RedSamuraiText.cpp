#include "RedSamuraiText.h"
#include "../Sound/Sound.h"
#include "../Texture/Sprite.h"
#include "../Game/Define.h"

Vector2 textPos = Vector2((float)WINDOW_WIDTH / 2, 150);
void RedSamuraiText::draw() const
{
	if (Sound::GetInstance().IsPlaySE(SE_ID::RED_START))
	{
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::KAKUGOWO, textPos);
	}

	if (Sound::GetInstance().IsPlaySE(SE_ID::RED_WIN))
	{
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::MOTTOREISEINI, textPos);
	}

	if (Sound::GetInstance().IsPlaySE(SE_ID::RED_LOSE))
	{
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::KOKODEHIKU, textPos);
	}
}
