#pragma once

#include "../Actor.h"

class Camera : public Actor
{
public:
	Camera(IWorld* world, std::weak_ptr<Actor> m_Player);

	void update(float deltaTime);

	virtual void draw() const override;
	//
	void move(
		const Vector3& rest_position, //�΂˂̐Î~�ʒu
		float stiffness,                //�΂˒萔(�΂˂̋���)
		float friction,                 //���C��
		float mass                      //����
	);

	void PlayerInput();

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