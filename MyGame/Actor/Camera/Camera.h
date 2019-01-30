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
		const Vector3& rest_position, //�΂˂̐Î~�ʒu
		float stiffness,                //�΂˒萔(�΂˂̋���)
		float friction,                 //���C��
		float mass                      //����
	);

	void PlayerInput();

	void TPS();
private:
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	Vector2 m_FarPoint{ 50.f,40.f };

	bool fps;
};