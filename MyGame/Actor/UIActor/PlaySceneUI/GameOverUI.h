#pragma once
#include "../../Actor.h"

class GameOverUI : public Actor {
public:
	GameOverUI(IWorld* world);
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const;

private:
	int GameOverBackAlpha;
};