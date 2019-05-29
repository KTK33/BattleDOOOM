#pragma once
#include "../Actor/Actor.h"

class RedSamuraiDeadUI : public Actor {
public:
	RedSamuraiDeadUI(IWorld* world);

	virtual void update(float deltaTime) override;

	virtual void draw() const;

private:
	bool mAlready;
};