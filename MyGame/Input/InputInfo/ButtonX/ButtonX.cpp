#include "ButtonX.h"
#include "../Input/InputInc.h"

const int Pad = PADBUTTON::NUM3;
const int key = KEYCODE::R;

bool ButtonX::TriggerDown()
{
	if (GamePad::GetInstance().ButtonTriggerDown(Pad)
		|| Keyboard::GetInstance().KeyTriggerDown(key))
	{
		return true;
	}
	return false;
}

bool ButtonX::TriggerUp()
{
	if (GamePad::GetInstance().ButtonTriggerUp(Pad)
		|| Keyboard::GetInstance().KeyTriggerUp(key))
	{
		return true;
	}
	return false;
}

bool ButtonX::StateDown()
{
	if (GamePad::GetInstance().ButtonStateDown(Pad)
		|| Keyboard::GetInstance().KeyStateDown(key))
	{
		return true;
	}
	return false;
}

bool ButtonX::StateUp()
{
	if (GamePad::GetInstance().ButtonStateUp(Pad)
		|| Keyboard::GetInstance().KeyStateUp(key))
	{
		return true;
	}
	return false;
}
