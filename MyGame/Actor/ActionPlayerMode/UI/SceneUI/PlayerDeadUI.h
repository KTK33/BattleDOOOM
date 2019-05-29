#pragma once
#include "../Actor/Actor.h"

class PlayerDeadUI : public Actor {
public:
	PlayerDeadUI(IWorld* world);

	virtual void update(float deltaTime) override;

	virtual void draw() const;

private:
	bool mAlready;
};