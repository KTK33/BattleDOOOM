#include "LeftStick.h"
#include "../../InputInc.h"

Vector2 LeftStick::GetAngle()
{
	Vector2 input;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT)) {
		input.x = -1.0f;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT)) {
		input.x = 1.0f;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP)) {
		input.y = 1.0f;

	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN)) {
		input.y = -1.0f;
	}

	input.x = GamePad::GetInstance().Stick().x;
	input.y = GamePad::GetInstance().Stick().y;

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
