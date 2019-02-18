#pragma once

#include "../Actor.h"
#include "../../Animation/AnimationMesh.h"
#include "../../Collision/BoundingCapsule.h"
#include "../Player/Player.h"
#include "../../Math/MathH.h"

class Ball : public Actor
{
public:
	Ball(int model, IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 1.0f, 2.0f));

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

protected:
	//ê^Ç¡íºÇÆî≠éÀÇ≥ÇÍÇÈíe
	void distance();

	//ìGÇ…å¸Ç©Ç¡ÇƒÇ¢Ç≠íe
	void homing();

	float target_angle() const;

private:
	AnimatedMesh mesh_;

	Actor* player_;

	Actor* enemy_;

	bool Hit;

	//íeÇÃÉXÉsÅ[Éh
	const float m_BallSPeed{ 1.0f };
	const float TurnAngle{ 2.5f };

	float deadTime;

	Vector3 m_InitFar{ 0.0f,0.0f,0.0f };
};