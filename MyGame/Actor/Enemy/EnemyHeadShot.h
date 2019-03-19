#pragma once

#include "../Actor.h"
#include "../../Math/MathH.h"
#include "../../Collision/BoundingSphere.h"

class EnemyHeadShot : public Actor
{
public:
	EnemyHeadShot(IWorld* world, const Vector3& position, std::weak_ptr<Actor> ene,const IBodyPtr& body = std::make_shared<BoundingSphere>(Vector3{ 0.0f,0.0f,0.0f }, 2.0f));

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

	virtual void onCollide(Actor& other);


private:
	std::weak_ptr<Actor> m_Enemy{};
};