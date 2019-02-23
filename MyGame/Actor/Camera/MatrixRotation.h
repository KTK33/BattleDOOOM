#pragma once
#include "../../Math/MathH.h"

class MatrixRotation {
public:
	MatrixRotation();
	void initialize(Matrix& rotation);
	Matrix update();
	Matrix eventUpdate();
	Matrix resetOnlyUpdate();
	void move(const bool& limit);
	void SetEventRotation(const Matrix& mat);
	void NormalReset(const Matrix& mat);
	void EventReset(const Matrix& start);
	float& sens();
private:
	float verticalangle_{ 0.f };//x軸の角度
	float horizontalangle_{ 0.f };//ｙ軸の角度
	float amount{ 0.0f };//Lerpのパーセント
	bool is_normalReset{ false };//通常時のリセット判定
	bool is_eventReset{ false };//イベント時のリセット判定
	Matrix endInitializeRotation{ Matrix::Identity };//Lerpのエンド
	float start_x{ 0.0f };
	float start_y{ 0.0f };
	float eRot{ 0.0f };
	float sens_{0.5f};
};