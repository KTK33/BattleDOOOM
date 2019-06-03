#include "RightStick.h"
#include "../../InputInc.h"

Vector2 RightStick::GetAngle()
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

	if (GetJoypadNum() >= 1) {
		input.x = GamePad::GetInstance().RightStick().x;
		input.y = GamePad::GetInstance().RightStick().y;
	}

	return input;
}
