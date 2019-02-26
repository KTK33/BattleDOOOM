#include "Sight.h"
#include "../../Texture/Sprite.h"
#include "../../Input/GamePad.h"

Sight::Sight(IWorld * world, const Vector3 & position):
	Actor(world,"Sight",position)
{
	m_GoPos = Vector3::Zero;
	AimCheck = false;
	p_rote = Matrix::Zero;
}

void Sight::initialize()
{
}

void Sight::update(float deltaTime)
{
}

void Sight::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::GETPLAYERPOS)
	{
		position_ = *(Vector3*)param;
	}
	if (message == EventMessage::SIGHT_CHECK)
	{
		AimCheck = *(bool*)param;
	}
	if (message == EventMessage::GETPLAYERROTATION)
	{
		p_rote = *(Matrix*)param;
	}
}

void Sight::draw() const
{
	if (AimCheck)
	{
		//Sprite::GetInstance().DrawBillBoard(SPRITE_ID::SIGHT,position_,Vector2(0.5f,0.5f), 3.0f);
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SIGHT, Vector2(ConvWorldPosToScreenPos(position_).x, ConvWorldPosToScreenPos(position_).y));
	}

	DrawFormatString(1000, 600, GetColor(255, 255, 255), "%f", ConvWorldPosToScreenPos(position_).x);
	DrawFormatString(1000, 700, GetColor(255, 255, 255), "%f", ConvWorldPosToScreenPos(position_).y);
}