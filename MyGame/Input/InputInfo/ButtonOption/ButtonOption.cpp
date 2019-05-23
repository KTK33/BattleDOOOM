#include "ButtonOption.h"
#include "../Input/InputInc.h"

const int Pad = PADBUTTON::NUM7;
const int key = KEYCODE::ESC;

bool ButtonOption::TriggerDown()
{
	if (GamePad::GetInstance().ButtonTriggerDown(Pad)
		|| Keyboard::GetInstance().KeyTriggerDown(key))
	{
		return true;
	}
	return false;
}

bool ButtonOption::TriggerUp()
{
	if (GamePad::GetInstance().ButtonTriggerUp(Pad)
		|| Keyboard::GetInstance().KeyTriggerUp(key))
	{
		return true;
	}
	return false;
}

bool ButtonOption::StateDown()
{
	if (GamePad::GetInstance().ButtonStateDown(Pad)
		|| Keyboard::GetInstance().KeyStateDown(key))
	{
		return true;
	}
	return false;
}

bool ButtonOption::StateUp()
{
	if (GamePad::GetInstance().ButtonStateUp(Pad)
		|| Keyboard::GetInstance().KeyStateUp(key))
	{
		return true;
	}
	return false;
}
