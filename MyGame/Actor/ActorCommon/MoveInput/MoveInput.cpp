#include "MoveInput.h"
#include "../Input/InputInc.h"

#include "../Input/InputInfoInc.h"

void MoveInput::Input(Vector2 & input)
{
	input = LeftStick::GetInstance().GetAngle();
}
