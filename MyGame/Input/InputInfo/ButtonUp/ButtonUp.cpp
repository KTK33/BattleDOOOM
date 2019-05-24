#include "ButtonUp.h"
#include "../Input/InputInc.h"

const int Pad = PADBUTTON::UP;
const int key = KEYCODE::UP;

bool ButtonUp::TriggerDown()
{
	if (GamePad::GetInstance().ButtonTriggerDown(Pad)
		|| Keyboard::GetInstance().KeyTriggerDown(key))
	{
		return true;
	}
	return false;
}

bool ButtonUp::TriggerUp()
{
	if (GamePad::GetInstance().ButtonTriggerUp(Pad)
		|| Keyboard::GetInstance().KeyTriggerUp(key))
	{
		return true;
	}
	return false;
}

bool ButtonUp::StateDown()
{
	if (GamePad::GetInstance().ButtonStateDown(Pad)
		|| Keyboard::GetInstance().KeyStateDown(key))
	{
		return true;
	}
	return false;
}

bool ButtonUp::StateUp()
{
	if (GamePad::GetInstance().ButtonStateUp(Pad)
		|| Keyboard::GetInstance().KeyStateUp(key))
	{
		return true;
	}
	return false;
}
