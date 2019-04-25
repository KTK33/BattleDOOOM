#include "Effect2D.h"

Effect2D::Effect2D(IWorld * world, Vector3 & position, int size, SPRITE_ID id):
	Actor(world,"Effect",position),
	size_{size},
	EffectID{id}
{
	effectTimer = 0;
	effectX = 0;
	effectY = 0;
}

void Effect2D::initialize()
{
}

void Effect2D::update(float deltaTime)
{
	effectTimer++;
	if (effectTimer % 1 == 0)
	{
		effectX = effectX + 1;
		if (effectX > 8)
		{
			effectY = effectY + 1;
			effectX = 0;
		}
	}

	if (effectY > 6) die();
}

void Effect2D::receiveMessage(EventMessage message, void * param)
{
}

void Effect2D::draw() const
{
	Vector2 SpriteSize = Sprite::GetInstance().GetSize(EffectID);

	Sprite::GetInstance().DrawPartRota(EffectID, Vector2(ConvWorldPosToScreenPos(position_).x, ConvWorldPosToScreenPos(position_).y),
		(int)SpriteSize.x / 8 * effectX,
		(int)SpriteSize.y / 6 * effectY,
		(int)SpriteSize.x / 8,
		(int)SpriteSize.y / 6,
		Vector2(SpriteSize.x/8/2,SpriteSize.y/6/2),
		Vector2(size_,size_)
	);
}
