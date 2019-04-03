#pragma once
#include "../Actor.h"
#include "../../Scene/Menu.h"

class PauseUI : public Actor ,public Menu{
public:
	PauseUI(IWorld* world);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

	void PlayerInput();

	void Pause();

	void SystemInput();

private:
	float UISize[4] = {};

	bool PauseDecision;

	bool areladySystemOpen;
};