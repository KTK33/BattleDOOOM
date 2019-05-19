#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Collision/BoundingSphere.h"
#include "../Math/MathH.h"

class ShootingPlayerBullet : public Actor
{
public:
	ShootingPlayerBullet(IWorld* world, const Vector3& P_position,Vector3& A_position,int AttackParam,const IBodyPtr& body = std::make_shared<BoundingSphere>(Vector3{ 0.0f,0.0f,0.0f }, 1.5f));
	virtual ~ShootingPlayerBullet() override{}

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void onCollide(Actor& other) override;

	virtual void draw() const override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	//壁と床の判定
	void collision();
private:
	Actor* player_;

	bool Hit;

	//弾のスピード
	const float m_BallSPeed{ 1.0f };
	const float TurnAngle{ 2.5f };

	Vector3 m_InitFar{ 0.0f,0.0f,0.0f };

	Vector3 m_GoPos;
};