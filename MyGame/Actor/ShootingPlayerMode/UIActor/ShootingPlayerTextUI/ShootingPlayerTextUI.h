#pragma once
#include "../Actor/Actor.h"

class ShootingPlayerTextUI : public Actor
{
public:
	ShootingPlayerTextUI(IWorld* world);
	virtual ~ShootingPlayerTextUI()override {}

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const override;

private:

	bool mGetBulletCheck;
	int mBulletTextTimer;
	bool mGetRecoverCheck;
	int mRecoverTextTimer;
	bool mAttackUpCheck;
	int mAttackUpTime;
};