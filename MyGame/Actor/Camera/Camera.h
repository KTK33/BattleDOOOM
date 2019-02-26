#pragma once

#include "../Actor.h"

class Camera : public Actor
{
public:
	Camera(IWorld* world);

	void update(float deltaTime);

	virtual void draw() const override;
	//
	void move(
		const Vector3& rest_position, //‚Î‚Ë‚ÌÃ~ˆÊ’u
		float stiffness,                //‚Î‚Ë’è”(‚Î‚Ë‚Ì‹­‚³)
		float friction,                 //–€C—Í
		float mass                      //¿—Ê
	);

	void PlayerInput();

private:
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	Vector2 m_FarPoint{ 0.f,0.f };

	float angle{ 0 };

	Vector2 AimPosMove;
};