#pragma once
//#include "../../Sound/Sound.h"

class Menu
{
protected:

	void moveCursor(int moveWidth)
	{
		// �J�[�\���̒l��ύX
		cursorPos_ += moveWidth;

		//Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::CURSOR_SE);

		// �J�[�\���ʒu���}�C�i�X�ɂȂ�Ȃ�ő�l�ɂ���
		if (cursorPos_ < 0) cursorPos_ = (menuSize_ - 1);

		// �J�[�\���ʒu���ő�l�𒴂���Ȃ�[���ɂ���
		if (cursorPos_ > (menuSize_ - 1)) cursorPos_ = 0;
	}


	void decisionCheck(){}
	void menuInit()
	{
		cursorPos_ = 0;
		isHighSpeedMove_ = false;
		longPressTimer_ = 0.0f;
	}

	int getCursorPos()
	{
		return cursorPos_;
	}

protected:

	int cursorPos_{ 0 };

	int menuSize_;

	// �������ɂ���ăJ�[�\���������œ��������H
	bool isHighSpeedMove_;

	float longPressTimer_;

	const float longPressTime_{ 0.25f };
};