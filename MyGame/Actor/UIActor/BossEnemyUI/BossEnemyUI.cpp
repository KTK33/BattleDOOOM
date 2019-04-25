#include "BossEnemyUI.h"
#include "../Texture/Sprite.h"

BossEnemyUI::BossEnemyUI(IWorld * world):
	Actor(world,"BOSSUI",Vector3::Zero),
	bossHP{InitbossHP}
{
}

void BossEnemyUI::initialize()
{
}

void BossEnemyUI::update(float deltaTime)
{
}

void BossEnemyUI::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::BOSSHP)
	{
		bossHP = *(int*)param;
	}
}

void BossEnemyUI::draw() const
{
	//HP
	Sprite::GetInstance().Draw(SPRITE_ID::BOSSHP_UI, Vector2(0, WINDOW_HEIGHT - Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_UI).y));
	Sprite::GetInstance().DrawPart(SPRITE_ID::BOSSHP_GAUGE, Vector2(492, WINDOW_HEIGHT - 70), 0, 0,
		Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_GAUGE).x / InitbossHP * bossHP, Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_GAUGE).y);

}
