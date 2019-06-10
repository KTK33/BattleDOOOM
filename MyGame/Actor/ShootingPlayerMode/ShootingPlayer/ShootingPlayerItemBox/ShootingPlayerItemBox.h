#pragma once

#include "../Actor/Actor.h"
#include "../Scene/Menu.h"
#include "../Actor/ActorState/ActorStateID.h"

class ShootingPlayerItemBox : public Actor,public Menu {
public:
	ShootingPlayerItemBox(IWorld* world, int HPItem,int AttackItem, std::weak_ptr<Actor> player);
	virtual ~ShootingPlayerItemBox()override{}

	virtual void initialize()override ;

	virtual void update(float deltaTime)override;

	virtual void draw() const override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	void PlayerInput();

private:

	std::weak_ptr<Actor> m_player{};

	int countHPrecoverItem;
	int countAttackUPItem;

	int alphaTimer;
	bool alphaCheck;

	int mPhp;
	ActorStateID mstate;
};