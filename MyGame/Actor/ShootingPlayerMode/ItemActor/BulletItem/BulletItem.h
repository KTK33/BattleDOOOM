#pragma once
#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Animation/AnimationMesh.h"

class BulletItem : public Actor{
public:
	BulletItem(int model,IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,4.0f,3.0f }, Matrix::Identity, 3.0f, 2.0f));
	virtual ~BulletItem()override{} 

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

private:
	//アニメーションメッシュ
	AnimatedMesh mesh_;
};
