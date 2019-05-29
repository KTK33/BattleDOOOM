#pragma once
#include "../Actor/Actor.h"
#include "../Texture/Sprite.h"

class Effect2D : public Actor
{
public:
	Effect2D(IWorld* world, Vector3 & position, int size, SPRITE_ID id);
	virtual ~Effect2D()override {}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:
	int size_;
	SPRITE_ID EffectID;

	int effectTimer;
	int effectX;
	int effectY;
};