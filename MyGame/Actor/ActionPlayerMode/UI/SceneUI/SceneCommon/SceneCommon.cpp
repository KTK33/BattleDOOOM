#include "SceneCommon.h"
#include "../Game/Define.h"
#include "../Texture/Sprite.h"

void SceneCommon::drawNext(int cursor) const
{
	switch (cursor)
	{
	case 0:
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::NEXTPLAY, Vector2((float)WINDOW_WIDTH / 2, 900));
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::NEXTTITLE_DEC, Vector2((float)WINDOW_WIDTH / 2, 1000));

		break;
	case 1:
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::NEXTPLAY_DEC, Vector2((float)WINDOW_WIDTH / 2, 900));
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::NEXTTITLE, Vector2((float)WINDOW_WIDTH / 2, 1000));
		break;
	default:
		break;
	}
}
