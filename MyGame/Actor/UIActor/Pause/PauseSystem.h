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

	void setPlayMode(int num);//0�̓V���[�e�B���O�A�P�̓A�N�V����

private:
	float bgmval;
	float seval;
	int aimval;

	int modenum{ 0 };
};