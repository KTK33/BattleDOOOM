#include "AcotrPush.h"

Vector3 ActorPush::Hit(Vector3 dir)
{
	const Vector3 dir_ = Vector3::Normalize(dir);
	Vector3 velocity;
	//アクターからプレイヤーの方向に移動
	velocity = Vector3::Up * 7.0f + Vector3{ dir_.x,0.0f,dir_.z } *2.0f;
	velocity.x = Vector3::Up.x * 7.0f + dir_.x*2.0f;
	velocity.z = Vector3::Up.z * 7.0f + dir_.z*2.0f;
	velocity.y = 0.0f;

	return velocity;
}
