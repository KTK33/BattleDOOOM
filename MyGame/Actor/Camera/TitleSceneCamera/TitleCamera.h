#pragma once

#include "../../Actor.h"

class TitleCamera : public Actor
{
public:
	TitleCamera(IWorld* world, std::weak_ptr<Actor> m_Player);
	virtual ~TitleCamera() override{}
		 
	virtual void update(float deltaTime) override;

	virtual void draw() const override;
	//
	void move(
		const Vector3& rest_position, //ばねの静止位置
		float stiffness,                //ばね定数(ばねの強さ)
		float friction,                 //摩擦力
		float mass                      //質量
	);

	void CameraMove();

private:
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	Vector2 m_FarPoint{ 0.f,0.f };

	float angle{ 0 };

	float cameraBack;

	std::weak_ptr<Actor> m_player{};

	Actor* bullet;
};