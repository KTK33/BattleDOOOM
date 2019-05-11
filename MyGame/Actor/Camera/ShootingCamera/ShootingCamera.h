#pragma once

#include "../../Actor.h"

class ShootingCamera : public Actor
{
public:
	ShootingCamera(IWorld* world, std::weak_ptr<Actor> m_Player);

	virtual void update(float deltaTime) override;

	virtual void draw() const override;
	//
	void move(
		const Vector3& rest_position, //‚Î‚Ë‚ÌÃ~ˆÊ’u
		float stiffness,                //‚Î‚Ë’è”(‚Î‚Ë‚Ì‹­‚³)
		float friction,                 //–€C—Í
		float mass                      //¿—Ê
	);

	void PlayerInput(float deltaTime);

	void PlayerGameFinish();

private:
	Actor* player_;
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	Vector2 m_FarPoint{ 30.f,20.f };

	float angle{ 0 };

	Vector2 AimPosMove;

	std::weak_ptr<Actor> m_player{};

	Vector3 DeadCamera{ 20,20,20 };
	bool alreadyGO;
};