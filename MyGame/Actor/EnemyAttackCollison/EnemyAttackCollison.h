#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Animation/AnimationMesh.h"


class EnemyAttackCollison : public Actor{
public:
	EnemyAttackCollison(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,5.0f,0.0f }, Matrix::Identity, 10.0f, 3.5f));

	void SetParam(bool deadCheck, int deadTime, int attackParam);

	void update(float deltaTime);

	void draw() const;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void* param);

private:
	bool mdeadCheck;
	int mdeadTime;
	int mattackparam;

};
