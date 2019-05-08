#pragma once

#include "../Actor/Actor.h"
#include "../Animation/AnimationMesh.h"
#include "../Collision/BoundingCapsule.h"
#include "../Collision/BoundingSegment.h"

class ArrowAttack : public Actor
{
public:
	//ArrowAttack(int model, IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 0.1f, 3.0f));
	ArrowAttack(int model, IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingSegment>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 10.0f));

	virtual void update(float deltaTime) override;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

	//ï«Ç∆è∞ÇÃîªíË
	void collision();

private:
	AnimatedMesh mesh_;
	Actor* player_;

	Vector3 plyaerVector;
};