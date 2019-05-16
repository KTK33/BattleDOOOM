#include "CameraSpring.h"

void CameraSpring::move(Vector3 & position, Vector3 & velocity, const Vector3 & rest_position, float stiffness, float friction, float mass)
{
	//ばねの伸び具合を計算
	const auto stretch = position - rest_position;
	//ばねの力を計算
	const auto force = -stiffness * stretch;
	//加速度を追加
	const auto acceleration = force / mass;
	//移動速度を計算
	velocity = friction * (velocity + acceleration);
	//座標の更新
	position += velocity;
}
