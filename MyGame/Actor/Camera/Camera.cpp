#include "Camera.h"
#include "../ActorGroup.h"
#include "../../Graphics/Graphics3D.h"
#include "../../Game/Define.h"

#include "../../Input/GamePad.h"

Camera::Camera(IWorld * world) :
	Actor(world, "Camera", Vector3::Zero)
{
}

void Camera::update(float deltaTime)
{
	Actor* player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
	const auto position = Vector3{ 0.0f,m_FarPoint.x,m_FarPoint.y } *player_->Getpose();
	target_ = player_->Getposition() + Vector3{ 0.0f,20.0f,0.0f };

	move(position, 1.0f, 0.2f, 0.8f);

	PlayerInput();
}

void Camera::draw() const
{

	Graphics3D::view_matrix(Matrix::CreateLookAt(position_,
		target_, { 0.0f,5.0f,0.0f }));
	Graphics3D::projection_matrix(Matrix::CreatePerspectiveFieldOfView(
		49.0f, 640.0f / 480.0f, 0.3f, 1000.0f));

	//�J�����̐ݒ�
//Graphics3D::view_matrix(Matrix::CreateLookAt(position_,
//	target_, { 0.0f,5.0f,0.0f }));
//Graphics3D::projection_matrix(Matrix::CreatePerspectiveFieldOfView(
//	49.0f, 640.0f / 480.0f, 0.3f, 1000.0f));
}

void Camera::move(const Vector3 & rest_position, float stiffness, float friction, float mass)
{
	//�΂˂̐L�ы���v�Z
	const auto stretch = position_ - rest_position;
	//�΂˂̗͂��v�Z
	const auto force = -stiffness * stretch;
	//�����x��ǉ�
	const auto acceleration = force / mass;
	//�ړ����x���v�Z
	velocity_ = friction * (velocity_ + acceleration);
	//���W�̍X�V
	position_ += velocity_;
}

void Camera::PlayerInput()
{
	if (CheckHitKey(KEY_INPUT_UP) ||
		GamePad::state(GamePad::Up))
	{
		if (m_FarPoint < Vector2(75.0f, 60.0f))
		{
			m_FarPoint += Vector2(FarSpeed, FarSpeed);
		}
	}

	if (CheckHitKey(KEY_INPUT_DOWN) ||
		GamePad::state(GamePad::Down))
	{
		if (Vector2(50.0f, 40.0f) < m_FarPoint)
		{
			m_FarPoint -= Vector2(FarSpeed, FarSpeed);
		}
	}

}
