#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Animation/AnimationMesh.h"


class ActionGameManager : public Actor {
public:
	ActionGameManager(IWorld* world, std::weak_ptr<Actor> player, std::weak_ptr<Actor> camera);
	virtual ~ActionGameManager() override {}

	virtual void update(float deltaTime) override;

private:
	std::weak_ptr<Actor> mPlayer{};
	std::weak_ptr<Actor> mCamera{};

	bool mTargetCamera;
};
