#pragma once

// 時間管理クラス
class Time {
public:
	// コンストラクタ
	Time();
	// インスタンス
	static Time &GetInstance();
	// 更新処理
	void update();
	// デルタタイムを返す
	float deltaTime();
	// fpsの表示
	void draw_fps();
private:
	float m_LastFrame;
	float m_LastTime;
	float m_RealtimeSinceStartup;
	float m_FrameCount;
	float m_DeltaTime;
private:
	int mCounter;
	int mFpsTime[2];
	int mFpsTime_i;
	float mFps;
};