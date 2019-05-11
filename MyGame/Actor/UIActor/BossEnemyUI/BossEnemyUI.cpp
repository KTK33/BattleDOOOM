#include "BossEnemyUI.h"
#include "../Texture/Sprite.h"

BossEnemyUI::BossEnemyUI(IWorld * world):
	Actor(world,"BOSSUI",Vector3::Zero),
	bossHP{InitbossHP}
{
}

void BossEnemyUI::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::BOSSHP)
	{
		bossHP = *static_cast<int*>(param);
	}
}

void BossEnemyUI::draw() const
{
	//HP
	Sprite::GetInstance().Draw(SPRITE_ID::BOSSHP_UI, Vector2(0, WINDOW_HEIGHT - Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_UI).y));
	Sprite::GetInstance().DrawPart(SPRITE_ID::BOSSHP_GAUGE, Vector2(492, WINDOW_HEIGHT - 70), 0, 0,
		static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_GAUGE).x / InitbossHP * bossHP), static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_GAUGE).y));
}
