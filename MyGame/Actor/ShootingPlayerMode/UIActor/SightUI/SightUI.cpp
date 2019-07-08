#include "SightUI.h"
#include "../Texture/Sprite.h"

void SightUI::initialize()
{
	mAimPos = Vector3::Zero;
	mAimCheck = false;
}

void SightUI::SetAimPos(Vector3 pos, bool check)
{
	mAimPos = pos;
	mAimCheck = check;
}

void SightUI::draw() const
{
	if (mAimCheck)
	{
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SIGHT, Vector2(ConvWorldPosToScreenPos(mAimPos).x, ConvWorldPosToScreenPos(mAimPos).y));
	}
}
