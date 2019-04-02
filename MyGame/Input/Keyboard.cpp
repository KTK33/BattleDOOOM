#include "Keyboard.h"

// コンストラクタ
Keyboard::Keyboard()
{
}

void Keyboard::InputStop()
{

	for (auto& k : m_keycode) {
		k = 0;
	}
	for (auto& k : m_prevkeycode) {
		k = 0;
	}
}

// キーを押した時のトリガー判定
bool Keyboard::KeyTriggerDown(UINT keycode)
{
	if (m_keycode[keycode] != 0 && m_prevkeycode[keycode] == 0)	return true;
	return false;
}

// キーを押した時のステート判定
bool Keyboard::KeyStateDown(UINT keycode)
{
	if (m_keycode[keycode] != 0)	return true;
	return false;
}

// キーを離した時のトリガー判定
bool Keyboard::KeyTriggerUp(UINT keycode)
{
	if (m_keycode[keycode] == 0 && m_prevkeycode[keycode] != 0)	return true;
	return false;
}

// キーを離した時のステート判定
bool Keyboard::KeyStateUp(UINT keycode)
{
	if (m_keycode[keycode] == 0)	return true;
	return false;
}

// いずれかのキーが入力されたか瞬間を調べる
bool Keyboard::AnyTriggerDown()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] != 0 && m_prevkeycode[i] == 0)	return true;
	}
	return false;
}

// いずれかのキーが入力されているか調べる
bool Keyboard::AnyStateDown()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] != 0)return true;
	}
	return false;
}

// いずれかのキーが離れたか瞬間を調べる
bool Keyboard::AnyTriggerUp()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] == 0 && m_prevkeycode[i] != 0)	return true;
	}
	return false;
}

// いずれかのキーが離れているか調べる
bool Keyboard::AnyStateUp()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] == 0)	return true;
	}
	return false;
}

// 更新処理
void Keyboard::Update()
{
	for (int i = 0; i < 256; i++) {
		m_prevkeycode[i] = m_keycode[i];

	}
	GetHitKeyStateAll(m_keycode);

}

