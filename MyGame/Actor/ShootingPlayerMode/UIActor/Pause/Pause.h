#pragma once
#include "../Actor/Actor.h"
#include "../Scene/Menu.h"

class PauseUI : public Actor ,public Menu{
public:
	PauseUI(IWorld* world);
	virtual ~PauseUI()override{}

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const override;

	void PlayerInput();

	void Pause();

	void SystemInput();

private:
	float UISize[4] = {};

	bool PauseDecision;

	bool areladySystemOpen;
};