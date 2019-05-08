#pragma once
#include "../Actor/Actor.h"

class RedSamuraiUI : public Actor {
public:
	RedSamuraiUI(IWorld* world);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

private:
	int m_samuraiHP;
};