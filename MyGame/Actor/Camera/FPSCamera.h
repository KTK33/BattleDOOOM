#pragma once
#include"../../Math/MathH.h"
#include"MatrixRotation.h"

class FPSCamera{
public:
	FPSCamera();//コンストラクタ
	void initialize(Matrix& rotation);//準備
	void update(Vector3 position);//通常時のFPSカメラの回転
	void EventUpdate(Vector3 position);//イベント時のFPSカメラの回転
	void StartUpdate(Vector3 position,Matrix& rotation);
	void ResetUpdate(Vector3 position);
	void camera_update(const Vector3& position,const Matrix& rotation);
	Matrix getRotation()const;//FPSカメラの回転行列取得
	void SetRotation(const Matrix& mat);
	void normalReset();//通常時のカメラリセット
	void eventReset();//イベント時のカメラリセット
	MatrixRotation rotationMat_;//stickによる視点移動
	float& getsens();
private:
	Matrix rotation_;//FPSカメラの回転行列
	Matrix endRotation_;//イベント時の固定角度
};