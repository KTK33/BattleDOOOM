#include "RedSamuraiUI.h"
#include "../Texture/Sprite.h"

RedSamuraiUI::RedSamuraiUI(IWorld * world):
	Actor(world,"RedSamuraiUI",Vector3::Zero),
	m_samuraiHP{0}
{
	initialize();
}

void RedSamuraiUI::initialize()
{
}

void RedSamuraiUI::update(float deltaTime)
{
}

void RedSamuraiUI::receiveMessage(EventMessage message, void * param)
{
	//ê‘éòÇÃHPÇéÛÇØéÊÇÈ
	if (message == EventMessage::SAMURAI_HP)
	{
		m_samuraiHP = *static_cast<int*>(param);
	}
}

void RedSamuraiUI::draw() const
{
	//HP
	Sprite::GetInstance().Draw(SPRITE_ID::BOSSHP_UI, Vector2(0, WINDOW_HEIGHT - Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_UI).y));
	Sprite::GetInstance().DrawPart(SPRITE_ID::BOSSHP_GAUGE, Vector2(492, WINDOW_HEIGHT - 70), 0, 0,
		static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_GAUGE).x / PlayerHP * m_samuraiHP),static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_GAUGE).y));

}
