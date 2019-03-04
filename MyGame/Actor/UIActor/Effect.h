#pragma once
#include "../Actor.h"
#include "../../Texture/Sprite.h"

class Effect : public Actor
{
public:
	Effect(IWorld* world, Vector3 & position, Vector3 distance, SPRITE_ID id);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

private:
	Vector3 P_distance;
	SPRITE_ID EffectID;

	int effectTimer;
	int effectX;
	int effectY;
};