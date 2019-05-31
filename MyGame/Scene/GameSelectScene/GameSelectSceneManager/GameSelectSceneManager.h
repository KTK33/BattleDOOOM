#pragma once

#include "../Actor/Actor.h"

class GameSelectSceneManager : public Actor {
public:
	GameSelectSceneManager(IWorld* world);
	virtual ~GameSelectSceneManager()override {}

	virtual void initialize()override;

	virtual void update(float deltaTime)override;

	virtual void draw() const override;

private:
};