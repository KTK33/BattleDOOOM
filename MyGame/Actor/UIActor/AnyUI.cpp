#include "AnyUI.h"
#include "../../Texture/Sprite.h"

AnyUI::AnyUI(IWorld * world):
	Actor(world,"AnyUI",Vector3::Zero)
{
}

void AnyUI::initialize()
{
	m_playerHP = 0;
}

void AnyUI::update(float deltaTime)
{
}

void AnyUI::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::PLAYER_HP)
	{
		m_playerHP = *(int*)param;
	}
}

void AnyUI::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::HP_UI, Vector2(0, WINDOW_HEIGHT));
	//Sprite::GetInstance().DrawPart(SPRITE_ID::HP_GAUGE, Vector2(168, WINDOW_HEIGHT - 22), 168, WINDOW_HEIGHT - 22,
	//	Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).x, Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).y);
	Sprite::GetInstance().DrawPart(SPRITE_ID::HP_GAUGE, Vector2(168, 22), 0, 0,
		Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).x / PlayerHP * m_playerHP, Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).y);

	Sprite::GetInstance().Draw(SPRITE_ID::TEXTFRAME, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::TEXTFRAME).x, WINDOW_HEIGHT));
}
