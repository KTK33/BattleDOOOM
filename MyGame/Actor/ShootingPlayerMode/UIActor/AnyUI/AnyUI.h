#pragma once
#include "../Actor/Actor.h"

class AnyUI : public Actor {
public:
	AnyUI(IWorld* world);

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

private:
	int mEnemyCount;
};