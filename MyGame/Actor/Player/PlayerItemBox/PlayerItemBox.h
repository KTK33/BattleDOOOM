#pragma once

#include "../Actor/Actor.h"
#include "../Scene/Menu.h"

class PlayerItemBox : public Actor,public Menu {
public:
	PlayerItemBox(IWorld* world, int HPItem,int AttackItem, std::weak_ptr<Actor> player);

	void initialize();

	void update(float deltaTime);

	void draw() const;

	virtual void receiveMessage(EventMessage message, void* param);

	void PlayerInput();

private:

	std::weak_ptr<Actor> m_player{};

	int countHPrecoverItem;
	int countAttackUPItem;

	int alphaTimer;
	bool alphaCheck;
};