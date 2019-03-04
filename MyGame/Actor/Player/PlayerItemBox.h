#pragma once

#include "../Actor.h"
#include "../../Scene/Menu.h"

class PlayerItemBox : public Actor,public Menu {
public:
	PlayerItemBox(IWorld* world, int HPItem);

	void initialize();

	void update(float deltaTime);

	void draw() const;

	virtual void receiveMessage(EventMessage message, void* param);

	void PlayerInput();

private:
	Actor* player_;

	int countHPrecoverItem;

};