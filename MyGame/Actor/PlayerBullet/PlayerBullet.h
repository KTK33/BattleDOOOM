#pragma once

#include "../Actor.h"
#include "../../Collision/BoundingCapsule.h"
#include "../../Collision/BoundingSphere.h"
#include "../Actor/Player/Player/Player.h"
#include "../../Math/MathH.h"

class PlayerBullet : public Actor
{
public:
	PlayerBullet(IWorld* world, const Vector3& P_position,Vector3& A_position,int AttackParam,const IBodyPtr& body = std::make_shared<BoundingSphere>(Vector3{ 0.0f,0.0f,0.0f }, 1.5f));
	virtual ~PlayerBullet() override{}

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void onCollide(Actor& other) override;

	virtual void draw() const override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	//壁と床の判定
	void collision();

protected:
	//真っ直ぐ発射される弾
	void distance();

	float target_angle() const;

private:
	Actor* player_;

	Actor* enemy_;

	bool Hit;

	//弾のスピード
	const float m_BallSPeed{ 1.0f };
	const float TurnAngle{ 2.5f };

	float deadTime;

	Vector3 m_InitFar{ 0.0f,0.0f,0.0f };

	Vector3 m_GoPos;
};