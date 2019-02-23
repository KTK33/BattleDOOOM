#pragma once

#include "../../Math/Vector3.h"

class TPSCamera
{
private:
	// カメラの視点座標クラス
	struct CPosition
	{
		Vector3 position_;
		Vector3 Get() const { return position_; }
		void Set(const Vector3& position) { position_ = position; }

	};

	// カメラの注視点座標クラス
	class CTarget
	{
	private:
		Vector3 target_;
	public:
		Vector3 Get() const { return target_; }
		void Set(const Vector3& target) { target_ = target; }
	};

	// カメラの上方向クラス
	struct CUp
	{
	private:
		Vector3 up_;
	public:
		Vector3 Get() const { return up_; }
		void Set(const Vector3& up) { up_ = up; }
	};

private:
	TPSCamera() = default;
	~TPSCamera() = default;

public:
	static TPSCamera& GetInstance()
	{
		static TPSCamera c;
		return c;
	}

	void Initialize();
	// 更新
	void Update();
	// カメラの描画距離を設定する（手前距離、奥距離）
	void SetRange(float Near, float Far);
	// カメラの回転角度を設定する（垂直回転角度、水平回転角度、捻り回転角度）
	void SetRotation(Vector3 rotate);
	// 指定した座標がカメラの視界に入っているか否か
	bool IsCheckView(Vector3 position);
	// 指定したボックス領域がカメラの視界に入っているか
	bool IsCheckView(Vector3 min, Vector3 max);
	// カメラの視野角を設定する（０～３６０度）
	void SetViewAngle(float degree);

public:
	CPosition	Position;
	CTarget		Target;
	CUp			Up;
	float near_, far_, degree_;
};