#pragma once

#include "../Actor/Actor.h"

class ActionModeManager : public Actor{
public:
	ActionModeManager(IWorld* world);
	virtual ~ActionModeManager()override {}

	virtual void initialize()override;

	virtual void update(float deltaTime)override;

	virtual void draw() const override;

private:
};