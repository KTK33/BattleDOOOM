#include "ActionPlayerUI.h"
#include "../Texture/Sprite.h"

ActionPlayerUI::ActionPlayerUI(IWorld * world):
	Actor(world, "ActionPlayerUI", Vector3::Zero),
	m_playerHP{0}
{
	initialize();
}

void ActionPlayerUI::initialize()
{
}

void ActionPlayerUI::update(float deltaTime)
{
}

void ActionPlayerUI::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::PLAYER_HP)
	{
		m_playerHP = *static_cast<int*>(param);
	}
}

void ActionPlayerUI::draw() const
{
	//HP
	Sprite::GetInstance().Draw(SPRITE_ID::HP_UI, Vector2(0, 0));
	Sprite::GetInstance().DrawPart(SPRITE_ID::HP_GAUGE, Vector2(169, 22), 0, 0,
		static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).x / PlayerHP * m_playerHP), static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).y));
	Sprite::GetInstance().Draw(SPRITE_ID::TEXTFRAME, Vector2(static_cast<float>(WINDOW_WIDTH) - Sprite::GetInstance().GetSize(SPRITE_ID::TEXTFRAME).x, 0));
}
