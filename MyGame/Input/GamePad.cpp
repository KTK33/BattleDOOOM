#include "GamePad.h"
#include<string>

GamePad::GamePad() :curStick_(Vector2::Zero), prevStick_(Vector2::Zero)
{
	m_inputbuttons.clear();
	m_onbuttons.clear();
	m_offbuttons.clear();
	m_pads.clear();
	m_onpovbuttons.clear();

	m_inputbuttons.push_back(PAD_INPUT_DOWN);
	m_inputbuttons.push_back(PAD_INPUT_UP);
	m_inputbuttons.push_back(PAD_INPUT_LEFT);
	m_inputbuttons.push_back(PAD_INPUT_RIGHT);
	m_inputbuttons.push_back(PAD_INPUT_1);
	m_inputbuttons.push_back(PAD_INPUT_2);
	m_inputbuttons.push_back(PAD_INPUT_3);
	m_inputbuttons.push_back(PAD_INPUT_4);
	m_inputbuttons.push_back(PAD_INPUT_5);
	m_inputbuttons.push_back(PAD_INPUT_6);
	m_inputbuttons.push_back(PAD_INPUT_7);
	m_inputbuttons.push_back(PAD_INPUT_8);
	m_inputbuttons.push_back(PAD_INPUT_9);
	m_inputbuttons.push_back(PAD_INPUT_10);
	m_inputbuttons.push_back(PAD_INPUT_11);
	m_inputbuttons.push_back(PAD_INPUT_12);

	m_pads.push_back(DX_INPUT_PAD1);
	m_pads.push_back(DX_INPUT_PAD2);
	m_pads.push_back(DX_INPUT_PAD3);
	m_pads.push_back(DX_INPUT_PAD4);
	for (auto& j : m_pads)
	{
		for (auto& i : m_inputbuttons)
		{
			m_onbuttons[j][i] = 0;
			m_offbuttons[j][i] = 0;
		}
		m_onpovbuttons[j] = 0;
	}
}

// 指定のパッドの指定のボタンが入力された瞬間か調べる
bool GamePad::ButtonTriggerDown(int button, int pad)
{
	Exception(pad, button);
	if (m_onbuttons[pad][button] == 1)
	{
		return true;
	}
	return false;
}

// 指定のパッドの指定のボタンが入力されているか調べる
bool GamePad::ButtonStateDown(int button, int pad)
{
	Exception(pad, button);
	if (m_onbuttons[pad][button] > 0)
	{
		return true;
	}
	return false;
}

// 指定のパッドの指定のボタンが離れた瞬間か調べる
bool GamePad::ButtonTriggerUp(int button, int pad)
{
	Exception(pad, button);
	if (m_offbuttons[pad][button] == 1)
	{
		return true;
	}
	return false;
}

// 指定のパッドの指定のボタンが離れているか調べる
bool GamePad::ButtonStateUp(int button, int pad)
{
	Exception(pad, button);
	if (m_offbuttons[pad][button] > 0)
	{
		return true;
	}
	return false;
}

// いずれかのボタンが入力された瞬間か調べる
bool GamePad::AnyTriggerDown(int pad)
{
	for (auto& button : m_inputbuttons)
	{
		Exception(pad, button);
		if (m_onbuttons[pad][button] == 1)
		{
			return true;
		}
	}
	return false;
}

// いずれかのボタンが入力されているか調べる
bool GamePad::AnyStateDown(int pad)
{
	for (auto& button : m_inputbuttons)
	{
		Exception(pad, button);
		if (m_onbuttons[pad][button] > 0)
		{
			return true;
		}
	}
	return false;
}

// いずれかのボタンが離れた瞬間か調べる
bool GamePad::AnyTriggerUp(int pad)
{
	for (auto& button : m_inputbuttons)
	{
		Exception(pad, button);
		if (m_offbuttons[pad][button] == 1)
		{
			return true;
		}
	}
	return false;
}

// いずれかのボタンが離れているか調べる
bool GamePad::AnyStateUp(int pad)
{
	for (auto& button : m_inputbuttons)
	{
		Exception(pad, button);
		if (m_offbuttons[pad][button] > 0)
		{
			return true;
		}
	}
	return false;
}

// 指定のパッドのPOVが入力された瞬間の方向を受け取る
int GamePad::POVTriggerDown(int pad)
{
	if (m_onpovbuttons[pad] != 1)
		return -1;

	return POVStateDown(pad);
}

// 指定のパッドのPOVが入力された方向を受け取る
int GamePad::POVStateDown(int pad)
{
	int result = GetJoypadPOVState(pad, 0);
	result = (result == -1) ? result : result / 100;
	return  result;
}

// 指定のパッドの右アナログスティックの入力具合を調べる
// (X = -1.0～1.0, Y = -1.0～1.0)
Vector2 GamePad::RightStick(int pad)
{
	int stickX, stickY;
	GetJoypadAnalogInputRight(&stickX, &stickY, pad);
	return Vector2((float)stickX / 1000.0f, (float)-stickY / 1000.0f);
}

// 指定のパッドのアナログスティックの入力具合を調べる
// (X = -1.0～1.0, Y = -1.0～1.0)
Vector2 GamePad::Stick(int pad)
{
	int stickX, stickY;
	GetJoypadAnalogInput(&stickX, &stickY, pad);
	return Vector2((float)stickX / 1000.0f, (float)-stickY / 1000.0f);
}

Vector2 GamePad::GetCurrentStick()
{
	return curStick_;
}

//前フレームの1番目コントローラのスティック入力を受け取る
Vector2 GamePad::GetPreviousStick()
{
	return prevStick_;
}

Vector2 GamePad::GetCurrentRightStick()
{
	return curRightStick_;
}

Vector2 GamePad::GetPreviousRightStick()
{
	return prevRightStick_;
}

// 指定のパッドの振動を開始する
void GamePad::VibrationStart(int power = 500, int time = 60, int pad)
{
	StartJoypadVibration(pad, power, time);

}

// 指定のパッドの振動を終了する
void GamePad::VibrationEnd(int pad)
{
	StopJoypadVibration(pad);
}

void GamePad::Update()
{
	for (auto& pad : m_pads)
	{
		for (auto& button : m_inputbuttons)
		{
			if ((GetJoypadInputState(pad) & button) == 0)
			{
				m_onbuttons[pad][button] = 0;
				m_offbuttons[pad][button]++;
			}
			else
			{
				m_offbuttons[pad][button] = 0;
				m_onbuttons[pad][button]++;
			}
		}
		if (GetJoypadPOVState(pad, 0) == -1)
		{
			m_onpovbuttons[pad] = 0;
		}
		else
		{
			m_onpovbuttons[pad]++;
		}
	}
	prevStick_ = curStick_;
	int stickX, stickY;
	GetJoypadAnalogInput(&stickX, &stickY, 1);
	curStick_ = Vector2((float)stickX / 1000.0f, (float)-stickY / 1000.0f);

	prevRightStick_ = curRightStick_;
	GetJoypadAnalogInputRight(&stickX, &stickY, 1);
	curRightStick_ = Vector2((float)stickX / 1000.0f, (float)-stickY / 1000.0f);

}

void GamePad::Exception(int pad, int button)
{
	if (m_onbuttons.find(pad) == m_onbuttons.end())
		throw std::string("残念ながら、指定したパッド番号は使用できません");

	if (m_onbuttons[pad].find(button) == m_onbuttons[pad].end())
		throw std::string("残念ながら、指定したボタン番号は使用できません");
}