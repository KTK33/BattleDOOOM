#pragma once
#include "../Actor.h"

class AnyUI : public Actor {
public:
	AnyUI(IWorld* world);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

private:
	int m_playerHP;
};