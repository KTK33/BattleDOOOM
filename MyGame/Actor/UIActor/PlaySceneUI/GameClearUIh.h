#pragma once
#include "../../Actor.h"

class GameClearUI : public Actor {
public:
	GameClearUI(IWorld* world);
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const;

private:
	int GameClearBackAlpha;
};