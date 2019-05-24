#include "DPad.h"
#include <DxLib.h>
#include "../Input/Keyboard/Keyboard.h"

int upkey =		KEYCODE::T;
int rightpkey = KEYCODE::H;
int downkey =	KEYCODE::G;
int leftkey =	KEYCODE::F;


bool DPad::GetUp()
{
	if (GetJoypadPOVState(DX_INPUT_PAD1, 0) == 0 ||
		Keyboard::GetInstance().KeyStateDown(upkey))
	{
		return true;
	}
	return false;
}

bool DPad::GetRight()
{
	if (GetJoypadPOVState(DX_INPUT_PAD1, 0) == 9000 ||
		Keyboard::GetInstance().KeyStateDown(rightpkey))
	{
		return true;
	}
	return false;
}

bool DPad::GetDown()
{
	if (GetJoypadPOVState(DX_INPUT_PAD1, 0) == 18000 ||
		Keyboard::GetInstance().KeyStateDown(downkey))
	{
		return true;
	}
	return false;
}

bool DPad::GetLeft()
{
	if (GetJoypadPOVState(DX_INPUT_PAD1, 0) == 27000 ||
		Keyboard::GetInstance().KeyStateDown(leftkey))
	{
		return true;
	}
	return false;
}
