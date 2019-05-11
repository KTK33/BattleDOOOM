#pragma once
#include "../Actor/Actor.h"

class BossEnemyUI : public Actor
{
public:
	BossEnemyUI(IWorld* world);
	virtual ~BossEnemyUI()override {}

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const override;

private:
	int InitbossHP{ 10 };
	int bossHP;
};