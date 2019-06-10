#include "BigBossHPUI.h"
#include "../Texture/Sprite.h"
#include "../Game/Define.h"

BigBossHPUI::BigBossHPUI(IWorld * world):
	Actor(world,"BigBossHP",Vector3::Zero),
	mhp{BigBossHPVal}
{
}

void BigBossHPUI::draw() const
{
	Sprite::GetInstance().DrawPart(SPRITE_ID::HP_GAUGE, Vector2(500, 1080 - Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).y), 0, 0,
		static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).x / BigBossHPVal * mhp), static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).y));
}

void BigBossHPUI::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::BOSSHP)
	{
		mhp = *static_cast<int*>(param);
	}
}
