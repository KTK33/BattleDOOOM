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

//横、高
int widthSize = 8;
int heightSize = 6;

void Effect2D::update(float deltaTime)
{
	//1/60秒で一つ隣の画像に移行
	effectTimer++;
	if (effectTimer % 1 == 0)
	{
		effectX = effectX + 1;
		if (effectX > widthSize) //最右に来たら一段下に行き最左に戻る
		{
			effectY = effectY + 1;
			effectX = 0;
		}
	}

	//描画が終了したら
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
