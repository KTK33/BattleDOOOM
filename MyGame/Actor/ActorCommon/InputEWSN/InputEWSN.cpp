#include "InputEWSN.h"
#include "../Input/InputInc.h"

void InputEWSN::Input(float & X, float & Y, float & yaw)
{
	if (GetJoypadNum() == 0) {
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A)) {
			X = -1.0f;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D)) {
			X = 1.0f;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)) {
			Y = 1.0f;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)) {
			Y = -1.0f;
		}

		//ÉvÉåÉCÉÑÅ[ÇÃâÒì]
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT)) {
			yaw = 1.0f;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT)) {
			yaw = -1.0f;
		}

	}
	else {
		X = GamePad::GetInstance().Stick().x;
		Y = GamePad::GetInstance().Stick().y;

		yaw = GamePad::GetInstance().RightStick().x;
	}


}
