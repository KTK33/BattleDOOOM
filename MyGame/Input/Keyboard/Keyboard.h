#pragma once

#include "DxLib.h"
#include <array>
#include "../InputType.h"

class Keyboard
{
private:
	Keyboard();
	~Keyboard() = default;

public:
	static Keyboard &GetInstance() {
		static Keyboard k;
		return k;
	}
	void InputStop();

	/// <summary>
	/// 指定されたキーが入力された瞬間か調べる
	/// </summary>
	bool KeyTriggerDown(UINT keycode);

	/// <summary>
	/// 指定されたキーが入力されているか調べる
	/// </summary>
	bool KeyStateDown(UINT keycode);

	/// <summary>
	/// 指定されたキーが離れた瞬間か調べる
	/// </summary>
	bool KeyTriggerUp(UINT keycode);

	/// <summary>
	/// 指定されたキーが離れているか調べる
	/// </summary>
	bool KeyStateUp(UINT keycode);

	/// <summary>
	/// いずれかのキーが入力された瞬間か調べる
	/// </summary>
	bool AnyTriggerDown();

	/// <summary>
	/// いずれかのキーが入力されているか調べる
	/// </summary>
	bool AnyStateDown();

	/// <summary>
	/// いずれかのキーが離れた瞬間か調べる
	/// </summary>
	bool AnyTriggerUp();

	/// <summary>
	/// いずれかのキーが離れているか調べる
	/// </summary>
	bool AnyStateUp();

	void Update();
private:
	char m_keycode[256];
	char m_prevkeycode[256];
};