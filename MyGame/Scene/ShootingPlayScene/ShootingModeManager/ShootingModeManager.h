#pragma once

#include "../Actor/Actor.h"

class ShootingModeManager : public Actor {
public:
	ShootingModeManager(IWorld* world);
	virtual ~ShootingModeManager()override {}

	virtual void initialize()override;

	virtual void update(float deltaTime)override;

	virtual void draw() const override;

private:
	bool BossArleady;
};