#include "Camera.h"
#include "../../Graphics/Graphics3D.h"
#include "../../Game/Define.h"

#include "../../Input/GamePad.h"
#include "../../Math/Vector2.h"

Camera::Camera(IWorld * world) :
	Actor(world, "Camera", Vector3::Zero)
{}

void Camera::update(float deltaTime)
{
	Actor* player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
	const auto position = Vector3{ 0.0f,m_FarPoint.x,m_FarPoint.y } *player_->Getpose();
	target_ = player_->Getposition() + Vector3{ 0.0f,20.0f,0.0f };
	move(position, 1.0f, 0.2f, 0.8f);

	if (world_->GetPauseCheck() == false){
		PlayerInput();
	}
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

	//DrawFormatString(600, 600, GetColor(255, 255, 255), "%f", GamePad::GetInstance().RightStick().y);

	//DrawFormatString(600, 700, GetColor(255, 255, 255), "%f", m_FarPoint.x);
	//DrawFormatString(600, 800, GetColor(255, 255, 255), "%f", m_FarPoint.y);

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
	m_FarPoint = Vector2::Clamp(m_FarPoint, Vector2(30.0f, 20.0f), Vector2(75.0f, 60.0f));

	m_FarPoint = m_FarPoint + GamePad::GetInstance().RightStick();


}
