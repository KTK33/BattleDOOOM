#include "MoveInput.h"
#include "../Input/InputInc.h"

#include "../Input/InputInfoInc.h"

void MoveInput::Input(Vector2 & input, float & yaw)
{
	input = LeftStick::GetInstance().GetAngle();
	yaw = RightStick::GetInstance().GetAngle().x;
}
