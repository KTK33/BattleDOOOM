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

	bool GetBulletCheck;
	int BulletTextTimer;
	bool GetRecoverCheck;
	int RecoverTextTimer;
	bool AttackUpCheck;
	int AttackUpTime;
};