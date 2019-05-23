#include "ButtonAll.h"
#include "../Input/InputInc.h"

bool ButtonAll::TriggerDown()
{
	if (GamePad::GetInstance().AnyTriggerDown() 
		|| Keyboard::GetInstance().AnyTriggerDown())
	{
		return true;
	}
	return false;
}

bool ButtonAll::TriggerUp()
{
	if (GamePad::GetInstance().AnyTriggerUp()
		|| Keyboard::GetInstance().AnyTriggerUp())
	{
		return true;
	}
	return false;
}

bool ButtonAll::StateDown()
{
	if (GamePad::GetInstance().AnyStateDown()
		|| Keyboard::GetInstance().AnyStateDown())
	{
		return true;
	}
	return false;
}

bool ButtonAll::StateUp()
{
	if (GamePad::GetInstance().AnyStateUp()
		|| Keyboard::GetInstance().AnyStateUp())
	{
		return true;
	}
	return false;
}
