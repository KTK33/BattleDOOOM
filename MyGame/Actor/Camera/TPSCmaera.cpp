#include "TPSCamera.h"
#include "../../Math/MathHelper.h"
#include <DxLib.h>

void TPSCamera::Initialize() {

	SetCameraNearFar(near_, far_);
	SetupCamera_Perspective(MathHelper::ToRadians(degree_));
	Update();
}
// �J�����̍X�V����
void TPSCamera::Update()
{
	SetCameraPositionAndTargetAndUpVec(
		VGet(Position.Get().x, Position.Get().y, Position.Get().z),
		VGet(Target.Get().x, Target.Get().y, Target.Get().z),
		VGet(Up.Get().x, Up.Get().y, Up.Get().z));
}

// �J�����̕`�拗����ݒ肷��i��O�`��A���`��j
void TPSCamera::SetRange(float Near, float Far)
{
	near_ = Near;
	far_ = Far;
	SetCameraNearFar(Near, Far);
}

// �J�����̉�]�p�x��ݒ肷��i���W�A������]�p�x�E������]�p�x�E�P���]�p�x�j
void TPSCamera::SetRotation(Vector3 rotate)
{
	SetCameraPositionAndAngle(
		VGet(Position.Get().x, Position.Get().y, Position.Get().z),
		rotate.x, rotate.y, rotate.z);
}

// �w�肵�����W���J�����̎��E�ɓ����Ă��邩�ۂ�
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

// �J�����̎���p��ݒ肷��
void TPSCamera::SetViewAngle(float degree)
{
	degree_ = degree;
	SetupCamera_Perspective(MathHelper::ToRadians(degree));
}
