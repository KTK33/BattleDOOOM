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
		const Vector3& rest_position, //ばねの静止位置
		float stiffness,                //ばね定数(ばねの強さ)
		float friction,                 //摩擦力
		float mass                      //質量
	);

	void PlayerInput();

	void TPS();
private:
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	Vector2 m_FarPoint{ 50.f,40.f };

	bool fps;
};