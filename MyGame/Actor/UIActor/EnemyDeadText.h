#pragma once
#include "../Actor.h"

class EnemyDeadText : public Actor
{
public:
	EnemyDeadText(IWorld* world);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

private:
	bool DeadEnemy{ false };
	bool DummyDeadEnemy{ false };
	int DummyDeadTextTime{ 90 };
};