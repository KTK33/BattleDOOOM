#include "LeftStick.h"
#include "../../InputInc.h"

Vector2 LeftStick::GetAngle()
{
	Vector2 input;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A)) {
		input.x = -1.0f;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D)) {
		input.x = 1.0f;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)) {
		input.y = 1.0f;

	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)) {
		input.y = -1.0f;
	}

	if (GetJoypadNum() >= 1){
		input.x = GamePad::GetInstance().Stick().x;
		input.y = GamePad::GetInstance().Stick().y;
	}

	input = Vector2::Clamp(input, Vector2(-1.0f, -1.0f), Vector2(1.0f, 1.0f));

	return input;
}

bool LeftStick::KnockCheck()
{
	bool check = false;

	if (GetAngle().x != 0.0f || GetAngle().y != 0.0f)
	{
		check = true;
	}

	return check;
}
