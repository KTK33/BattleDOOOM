#pragma once
#include "../Actor.h"

class BossEnemyUI : public Actor
{
public:
	BossEnemyUI(IWorld* world);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

private:
	int InitbossHP{ 10 };
	int bossHP;
};