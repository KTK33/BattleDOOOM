#pragma once
#include "../Actor/Actor.h"

class GameClearUI : public Actor {
public:
	GameClearUI(IWorld* world);
	virtual ~GameClearUI() override{}

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:
	int GameClearBackAlpha;
};