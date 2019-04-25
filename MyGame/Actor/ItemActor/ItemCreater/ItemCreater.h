#pragma once
#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Animation/AnimationMesh.h"

class ItemCreater : public Actor {
public:
	ItemCreater(IWorld* world, const Vector3& position);

	void initialize() override;

	void update(float deltaTime);

	virtual void receiveMessage(EventMessage message, void * param) override;

private:
};
