#pragma once
#include "../Actor/Actor.h"
#include "../Scene/Menu.h"

class ActionModePause : public Actor, public Menu {
public:
	ActionModePause(IWorld* world);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const override;

	//����
	void PlayerInput();

	void SystemInput();

private:
	bool PauseDecision; //�|�[�Y�̌�����

	bool areladySystemOpen;
};