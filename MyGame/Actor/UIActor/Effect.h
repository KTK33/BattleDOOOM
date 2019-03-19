#pragma once
#include "../Actor.h"
#include "../../Texture/Sprite.h"

class Effect : public Actor
{
public:
	Effect(IWorld* world, Vector3 & position, int size, SPRITE_ID id);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

private:
	int size_;
	SPRITE_ID EffectID;

	int effectTimer;
	int effectX;
	int effectY;
};