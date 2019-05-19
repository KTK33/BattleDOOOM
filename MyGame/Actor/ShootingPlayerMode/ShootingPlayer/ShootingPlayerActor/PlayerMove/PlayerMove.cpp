#include "PlayerMove.h"
#include "../Sound/Sound.h"

void PlayerMove::Move(Vector3 & pos, Vector3 & vel, Matrix rote, float speed, Vector2 input)
{
	//ëOå„ç∂âEà⁄ìÆ
	vel = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };

	side_speed = -input.x * speed;
	forward_speed = input.y * speed;

	vel += rote.Forward() * forward_speed;
	vel += rote.Left() * side_speed;
	pos += vel * 1.0f;

	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::WALKSTEP_SE);

}
