#pragma once

#include "../Actor/Actor.h"
#include "../Animation/AnimationMesh.h"
#include "../Collision/BoundingSegment.h"

class ArrowAttack : public Actor
{
public:
	ArrowAttack(int model, IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingSegment>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 10.0f));
	~ArrowAttack() {};

	virtual void update(float deltaTime) override;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

	//�ǂƏ��̔���
	void collision();

private:
	AnimatedMesh mesh_;
	Actor* player_;

	Vector3 plyaerVector;
};