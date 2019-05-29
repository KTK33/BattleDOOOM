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

//���A��
int widthSize = 8;
int heightSize = 6;

void Effect2D::update(float deltaTime)
{
	//1/60�b�ň�ׂ̉摜�Ɉڍs
	effectTimer++;
	if (effectTimer % 1 == 0)
	{
		effectX = effectX + 1;
		if (effectX > widthSize) //�ŉE�ɗ������i���ɍs���ō��ɖ߂�
		{
			effectY = effectY + 1;
			effectX = 0;
		}
	}

	//�`�悪�I��������
	if (effectY > heightSize) die();
}

void Effect2D::draw() const
{
	const Vector2 SpriteSize = Sprite::GetInstance().GetSize(EffectID);

	Sprite::GetInstance().DrawPartRota(EffectID, Vector2(ConvWorldPosToScreenPos(position_).x, ConvWorldPosToScreenPos(position_).y),
		(int)SpriteSize.x / widthSize * effectX,
		(int)SpriteSize.y / heightSize * effectY,
		(int)SpriteSize.x / widthSize,
		(int)SpriteSize.y / heightSize,
		Vector2(SpriteSize.x / widthSize / 2,
			    SpriteSize.y / heightSize / 2),
		Vector2(static_cast<float>(size_), static_cast<float>(size_))
	);
}
