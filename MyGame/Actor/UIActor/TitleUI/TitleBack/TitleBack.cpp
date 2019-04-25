#include "TitleBack.h"
#include "../Texture/Sprite.h"

TitleBack::TitleBack(IWorld * world):
	Actor(world,"TitleBack",Vector3::Zero),
	TitleBackAlpha{ 0 }
{
}

void TitleBack::initialize()
{
}

void TitleBack::update(float deltaTime)
{
	TitleBackAlpha = min(TitleBackAlpha + 5, 255);
}

void TitleBack::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, TitleBackAlpha);
	Sprite::GetInstance().Draw(SPRITE_ID::TITLEBACK, Vector2(0, 0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
