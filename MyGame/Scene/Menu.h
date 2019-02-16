#pragma once
//#include "../../Sound/Sound.h"

class Menu
{
protected:

	void moveCursor(int moveWidth)
	{
		// カーソルの値を変更
		cursorPos_ += moveWidth;

		//Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::CURSOR_SE);

		// カーソル位置がマイナスになるなら最大値にする
		if (cursorPos_ < 0) cursorPos_ = (menuSize_ - 1);

		// カーソル位置が最大値を超えるならゼロにする
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

	// 長押しによってカーソルを高速で動かすか？
	bool isHighSpeedMove_;

	float longPressTimer_;

	const float longPressTime_{ 0.25f };
};