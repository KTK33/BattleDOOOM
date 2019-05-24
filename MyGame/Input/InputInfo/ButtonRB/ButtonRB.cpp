#include "ButtonRB.h"
#include "../Input/InputInc.h"

const int Pad = PADBUTTON::NUM6;
const int key = KEYCODE::R;

bool ButtonRB::TriggerDown()
{
	if (GamePad::GetInstance().ButtonTriggerDown(Pad)
		|| Keyboard::GetInstance().KeyTriggerDown(key))
	{
		return true;
	}
	return false;
}

bool ButtonRB::TriggerUp()
{
	if (GamePad::GetInstance().ButtonTriggerUp(Pad)
		|| Keyboard::GetInstance().KeyTriggerUp(key))
	{
		return true;
	}
	return false;
}

bool ButtonRB::StateDown()
{
	if (GamePad::GetInstance().ButtonStateDown(Pad)
		|| Keyboard::GetInstance().KeyStateDown(key))
	{
		return true;
	}
	return false;
}

bool ButtonRB::StateUp()
{
	if (GamePad::GetInstance().ButtonStateUp(Pad)
		|| Keyboard::GetInstance().KeyStateUp(KEYCODE::E))
	{
		return true;
	}
	return false;
}
