#include "ButtonY.h"
#include "../Input/InputInc.h"

const int Pad = PADBUTTON::NUM4;
const int key = KEYCODE::Q;

bool ButtonY::TriggerDown()
{
	if (GamePad::GetInstance().ButtonTriggerDown(Pad)
		|| Keyboard::GetInstance().KeyTriggerDown(key))
	{
		return true;
	}
	return false;
}

bool ButtonY::TriggerUp()
{
	if (GamePad::GetInstance().ButtonTriggerUp(Pad)
		|| Keyboard::GetInstance().KeyTriggerUp(key))
	{
		return true;
	}
	return false;
}

bool ButtonY::StateDown()
{
	if (GamePad::GetInstance().ButtonStateDown(Pad)
		|| Keyboard::GetInstance().KeyStateDown(key))
	{
		return true;
	}
	return false;
}

bool ButtonY::StateUp()
{
	if (GamePad::GetInstance().ButtonStateUp(Pad)
		|| Keyboard::GetInstance().KeyStateUp(key))
	{
		return true;
	}
	return false;
}
