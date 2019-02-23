#pragma once

#include "../Actor.h"
#include "../Player/Player.h"
#include "../../Math/MathH.h"

class Sight : public Actor
{
public:
	Sight(int model, IWorld* world, const Vector3& P_position);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

private:
	Vector2 m_GoPos;
};