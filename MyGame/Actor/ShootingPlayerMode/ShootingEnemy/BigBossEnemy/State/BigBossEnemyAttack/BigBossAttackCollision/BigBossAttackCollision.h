#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Animation/AnimationMesh.h"
#include "CollisionMove/CollisionMove.h"


class BigBossAttackCollision : public Actor {
public:
	BigBossAttackCollision(IWorld* world, const Vector3& position, const Matrix & rotation, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,5.0f,0.0f }, Matrix::Identity, 10.0f, 3.5f));
	virtual ~BigBossAttackCollision()override {}

	void SetParam(bool deadCheck, int deadTime, int attackParam,int attacktype);

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void* param);
	
private:
	void AttackType(int type);
private:
	bool mdeadCheck;
	int mdeadTime;
	int mattackparam;
	int mattacktype;

	int mattacktime;

	CollisionMove mCM;
};
