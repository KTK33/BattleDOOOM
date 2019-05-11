#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Animation/AnimationMesh.h"


class PlayerAttackCollision : public Actor {
public:
	PlayerAttackCollision(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,5.0f,0.0f }, Matrix::Identity, 10.0f, 3.5f));
	virtual ~PlayerAttackCollision()override{}

	void SetParam(bool leaveCheck, int deadTime, int attackParam);

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void* param);

private:
	bool mdeadCheck;
	int mdeadTime;
	int mattackparam;

};
