#pragma once

#include "../Actor/Actor.h"
#include "../Scene/Menu.h"

class PauseSystem : public Actor, public Menu {
public:
	PauseSystem(IWorld* world);
	virtual ~PauseSystem()override{}

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void receiveMessage(EventMessage message, void* param) override;

	void PlayerInput();

	void setPlayMode(int num);//0はシューティング、１はアクション

private:
	float bgmval;
	float seval;
	int aimval;

	int modenum{ 0 };
};