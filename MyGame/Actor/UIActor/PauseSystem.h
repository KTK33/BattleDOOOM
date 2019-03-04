#pragma once

#include "../Actor.h"
#include "../../Scene/Menu.h"

class PauseSystem : public Actor, public Menu {
public:
	PauseSystem(IWorld* world);

	void initialize();

	void update(float deltaTime);

	void draw() const;

	virtual void receiveMessage(EventMessage message, void* param);

	void PlayerInput();

private:
	int bgmval;
	int seval;
	int aimval;
};