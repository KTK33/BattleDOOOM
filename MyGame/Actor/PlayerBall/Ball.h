#pragma once

#include "../Actor.h"
#include "../../Animation/AnimationMesh.h"
#include "../../Collision/BoundingCapsule.h"
#include "../Player/Player.h"
#include "../../Math/MathH.h"

class Ball : public Actor
{
public:
	Ball(int model, IWorld* world, const Vector3& P_position,Vector2& A_position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 1.0f, 2.0f));

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

protected:
	//真っ直ぐ発射される弾
	void distance();

	//敵に向かっていく弾
	void homing();

	float target_angle() const;

private:
	AnimatedMesh mesh_;

	Actor* player_;

	Actor* enemy_;

	bool Hit;

	//弾のスピード
	const float m_BallSPeed{ 1.0f };
	const float TurnAngle{ 2.5f };

	float deadTime;

	Vector3 m_InitFar{ 0.0f,0.0f,0.0f };

	Vector2 m_GoPos;
};