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
	/// �w�肳�ꂽ�L�[�����͂��ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool KeyTriggerDown(UINT keycode);

	/// <summary>
	/// �w�肳�ꂽ�L�[�����͂���Ă��邩���ׂ�
	/// </summary>
	bool KeyStateDown(UINT keycode);

	/// <summary>
	/// �w�肳�ꂽ�L�[�����ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool KeyTriggerUp(UINT keycode);

	/// <summary>
	/// �w�肳�ꂽ�L�[������Ă��邩���ׂ�
	/// </summary>
	bool KeyStateUp(UINT keycode);

	/// <summary>
	/// �����ꂩ�̃L�[�����͂��ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool AnyTriggerDown();

	/// <summary>
	/// �����ꂩ�̃L�[�����͂���Ă��邩���ׂ�
	/// </summary>
	bool AnyStateDown();

	/// <summary>
	/// �����ꂩ�̃L�[�����ꂽ�u�Ԃ����ׂ�
	/// </summary>
	bool AnyTriggerUp();

	/// <summary>
	/// �����ꂩ�̃L�[������Ă��邩���ׂ�
	/// </summary>
	bool AnyStateUp();

	void Update();
private:
	char m_keycode[256];
	char m_prevkeycode[256];
};