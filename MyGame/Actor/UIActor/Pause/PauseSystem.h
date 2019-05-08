#pragma once

#include "../Actor/Actor.h"
#include "../Scene/Menu.h"

class PauseSystem : public Actor, public Menu {
public:
	PauseSystem(IWorld* world);

	void initialize();

	void update(float deltaTime);

	void draw() const;

	virtual void receiveMessage(EventMessage message, void* param);

	void PlayerInput();

	void setPlayMode(int num);//0はシューティング、１はアクション

private:
	float bgmval;
	float seval;
	int aimval;

	int modenum{ 0 };
};