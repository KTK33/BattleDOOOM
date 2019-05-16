#pragma once
#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Animation/AnimationMesh.h"

class ItemCreater : public Actor {
public:
	ItemCreater(IWorld* world, const Vector3& position);
	virtual ~ItemCreater() override{}

	virtual void initialize() override;

	virtual void update(float deltaTime)override;

	virtual void receiveMessage(EventMessage message, void * param) override;

private:
};
