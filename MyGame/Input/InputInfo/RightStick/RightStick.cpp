#include "RightStick.h"
#include "../../InputInc.h"

Vector2 RightStick::GetAngle()
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

	input.x = GamePad::GetInstance().RightStick().x;
	input.y = GamePad::GetInstance().RightStick().y;

	return input;
}
