#pragma once

#include "../Actor.h"
#include "../../Animation/AnimationMesh.h"
#include "../../Collision/BoundingSphere.h"

class EnemyAttackFire : public Actor
{
public:
	EnemyAttackFire(int model, IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingSphere>(Vector3{ 0.0f,0.0f,0.0f },3.0f));

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

	void GetEnemyForward(Vector3 forward);

private:
	AnimatedMesh mesh_;
	Actor* player_;

	Vector3 EnemyForward;

	int DeadTimer{ 0 };

	Vector3 plyaerVector;
};