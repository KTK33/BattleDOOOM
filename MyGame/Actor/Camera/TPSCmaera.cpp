#include "TPSCamera.h"
#include "../../Math/MathHelper.h"
#include <DxLib.h>

void TPSCamera::Initialize() {

	SetCameraNearFar(near_, far_);
	SetupCamera_Perspective(MathHelper::ToRadians(degree_));
	Update();
}
// カメラの更新処理
void TPSCamera::Update()
{
	SetCameraPositionAndTargetAndUpVec(
		VGet(Position.Get().x, Position.Get().y, Position.Get().z),
		VGet(Target.Get().x, Target.Get().y, Target.Get().z),
		VGet(Up.Get().x, Up.Get().y, Up.Get().z));
}

// カメラの描画距離を設定する（手前描画、奥描画）
void TPSCamera::SetRange(float Near, float Far)
{
	near_ = Near;
	far_ = Far;
	SetCameraNearFar(Near, Far);
}

// カメラの回転角度を設定する（座標、垂直回転角度・水平回転角度・捻り回転角度）
void TPSCamera::SetRotation(Vector3 rotate)
{
	SetCameraPositionAndAngle(
		VGet(Position.Get().x, Position.Get().y, Position.Get().z),
		rotate.x, rotate.y, rotate.z);
}

// 指定した座標がカメラの視界に入っているか否か
bool TPSCamera::IsCheckView(Vector3 position)
{
	return CheckCameraViewClip(VGet(position.x, position.y, position.z));
}

bool TPSCamera::IsCheckView(Vector3 min, Vector3 max)
{
	return CheckCameraViewClip_Box(
		VGet(min.x, min.y, min.z),
		VGet(max.x, max.y, max.z));
}

// カメラの視野角を設定する
void TPSCamera::SetViewAngle(float degree)
{
	degree_ = degree;
	SetupCamera_Perspective(MathHelper::ToRadians(degree));
}
