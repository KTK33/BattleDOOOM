#include "Camera.h"
#include "../../World/IWorld.h"
#include "../ActorGroup.h"

Camera::Camera(IWorld & world,Vector3& position):
	player_{ nullptr }
{
	world_ = &world;
	position_ = position;
}

void Camera::initialize()
{
	Angle = 0.0f;
	//カメラの向きを初期化
	CameraHAngle = 0.0f;
	CameraVAngle = 40.0f;
	SetCameraNearFar(100.0f, 50000.0f);
}

void Camera::update(float deltaTime)
{
	//(void)deltaTime;
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
	//const auto position = Vector3{ 0.0f,3.0f,-6.0f } *player_->pose();
	//target_ = player_->pose().Translation().x + Vector3{ 0.0f,2.0f,0.0f };

	Vector3 p_pos = player_->pose().Translation();
	m_pos = player_->pose().Translation();

	// 移動しているかどうかのフラグを倒す
	Moveflag = FALSE;

	if (GamePad::state(GamePad::Up))
	{
		Angle = 18.0f - CameraHAngle;
		Moveflag = true;
	}
	else if (GamePad::state(GamePad::Down))
	{
		Angle = 0.0f - CameraHAngle;
		Moveflag = true;
	}
	else if (GamePad::state(GamePad::Left))
	{
		Angle = 90.0f - CameraHAngle;
		Moveflag = true;
	}
	else if (GamePad::state(GamePad::Right))
	{
		Angle = -90.0f - CameraHAngle;
		Moveflag = true;
	}

	if (Moveflag)
	{
		Vector3 TempMoveVector;
	}


	//CameraMove();
	//CameraCalculation(p_pos);
}

void Camera::draw() const
{
	//DrawFormatString(100, 100, GetColor(255, 255, 255), "%f", m_pos);
	//SetCameraPositionAndTargetAndUpVec(VGet(player_->pose().Translation().x, 10, 50.0f), Vector3{ player_->pose().Translation().x,10,0.0f }, Vector3::Up);
	//カメラの設定
	//Graphics3D::view_matrix(Matrix::CreateLookAt(position_,
	//	target_, { 0.0f,15.0f,0.0f }));
	//Graphics3D::projection_matrix(Matrix::CreatePerspectiveFieldOfView(
	//	49.0f, 640.0f / 480.0f, 0.3f, 1000.0f));

	//カメラの設定
	Graphics3D::view_matrix(Matrix::CreateLookAt({ 0.0f,46.0f,80.0f },
		{ 0.0f,31.0f,0.0f }, { 0.0f,2.0f,5.0f }));
	Graphics3D::projection_matrix(Matrix::CreatePerspectiveFieldOfView(
		49.0f, 640.0f / 480.0f, 0.3f, 1000.0f));

}

void Camera::CameraMove()
{
	//カメラの操作
	if (CheckHitKey(KEY_INPUT_X) == 1)
	{
		CameraHAngle += CAMERA_ANGLE_SPEED;
		if (CameraHAngle >= 180.0f)
		{
			CameraHAngle -= 360.0f;
		}
	}

	if (CheckHitKey(KEY_INPUT_C) == 1)
	{
		CameraHAngle -= CAMERA_ANGLE_SPEED;
		if (CameraHAngle <= -180.0f)
		{
			CameraHAngle += 360.0f;
		}
	}

	if (CheckHitKey(KEY_INPUT_Z) == 1)
	{
		CameraVAngle += CAMERA_ANGLE_SPEED;
		if (CameraVAngle >= 80.0f)
		{
			CameraVAngle = 80.0f;
		}
	}

	if (CheckHitKey(KEY_INPUT_V) == 1)
	{
		CameraVAngle -= CAMERA_ANGLE_SPEED;
		if (CameraVAngle <= 0.0f)
		{
			CameraVAngle = 0.0f;
		}
	}
}

void Camera::CameraCalculation(Vector3 pos)
{
	DrawFormatString(400, 400, GetColor(255, 255, 255), "%f", pos);
	Vector3 TempPosition1;
	Vector3 TempPosition2;
	Vector3 CameraPosition;
	Vector3 CameraLookAtPosition;

	CameraLookAtPosition = pos;
	CameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;

	CameraPosition = VAdd(TempPosition2, CameraLookAtPosition);

	SetCameraPositionAndTarget_UpVecY(CameraPosition, CameraLookAtPosition);
}

