#pragma once

#include "../Actor/Actor.h"

class ActionCamera : public Actor
{
public:
	ActionCamera(IWorld* world, std::weak_ptr<Actor> m_Player);

	void update(float deltaTime);

	virtual void draw() const override;
	//
	void move(
		const Vector3& rest_position, //ばねの静止位置
		float stiffness,                //ばね定数(ばねの強さ)
		float friction,                 //摩擦力
		float mass                      //質量
	);

	void PlayerInput(float deltaTime);

	virtual void receiveMessage(EventMessage message, void * param) override;

private:
	Actor* player_;
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	Vector2 m_FarPoint{ 30.f,20.f };

	std::weak_ptr<Actor> m_player{};

	//ターゲットからのオフセット
	Vector3 m_Offset;
	//カメラの上方向ベクトル
	Vector3 m_Up;
	//ピッチの角速度
	float m_PitchSpeed;
	//ヨーの角速度
	float m_YawSpeed;

	int PlayerHeight{ 15 };

	bool mTargetCamera;
};