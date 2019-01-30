#include "Time.h"

#include <DxLib.h>

// コンストラクタ
Time::Time() :
	m_LastFrame(0), m_LastTime(0), m_RealtimeSinceStartup(0), m_FrameCount(0), m_DeltaTime(0),
	mCounter(0), mFpsTime{ 0, 0 }, mFpsTime_i(0), mFps(0.0f) {
}

// インスタンス
Time & Time::GetInstance() {
	static Time instance;
	return instance;
}

// 更新処理
void Time::update() {
	m_FrameCount++;
	m_RealtimeSinceStartup = m_FrameCount / 60;

	float currentFrame = m_FrameCount;
	if (currentFrame != m_LastFrame) {
		float currentTime = m_RealtimeSinceStartup;
		m_DeltaTime = currentTime - m_LastTime;
		m_LastTime = currentTime;
		m_LastFrame = currentFrame;
	}
}

// デルタタイムを返す
float Time::deltaTime() {
	return m_DeltaTime;
}

#ifdef NDEBUG
void Time::draw_fps() {}
#else
// fpsの表示
void Time::draw_fps() {
	if (mFpsTime_i == 0)
		mFpsTime[0] = GetNowCount();               //1周目の時間取得
	if (mFpsTime_i == 49) {
		mFpsTime[1] = GetNowCount();               //50周目の時間取得
		mFps = 1000.0f / ((mFpsTime[1] - mFpsTime[0]) / 50.0f);//測定した値からfpsを計算
		mFpsTime_i = 0;//カウントを初期化
	}
	else
		mFpsTime_i++;//現在何周目かカウント
	if (mFps != 0)
		DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS %.1f", mFps); //fpsを表示
}
#endif