#include "Camera.h"
#include "../../Graphics/Graphics3D.h"
#include "../../Game/Define.h"

#include "../../Input/GamePad.h"
#include "../../Math/Vector2.h"

#include "TPSCamera.h"

Camera::Camera(IWorld * world) :
	Actor(world, "Camera", Vector3::Zero)
{
}

void Camera::update(float deltaTime)
{
	Actor* player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
	const auto position = Vector3{ 0.0f,m_FarPoint.x,m_FarPoint.y } *player_->Getpose();
	//target_ = player_->Getposition(); /*+Vector3{ 0.0f,10.0f,0.0f }*/;
	//target_ = player_->Getposition() + player_->Getrotation().Forward() *5;
	if (world_->GetPauseCheck() == false){
		PlayerInput();
	}

	float XX = GamePad::GetInstance().RightStick().x;
	float YY = GamePad::GetInstance().RightStick().y;

	//position_.x += GamePad::GetInstance().RightStick().x * 10;
	//position_.z += GamePad::GetInstance().RightStick().x * 10;

	Vector3 P_T = Vector3::Distance(position_, target_);
	//P_T = Vector3::Clamp(P_T, Vector3(0, 0, 0), Vector3(10, 10, 10));

	//Vector3 fw = Vector3::CreateFromYawPitch(XX, target_.x);

	//angle += XX;
	//position_.x += MathHelper::Sin(angle) * P_T.x;
	//position_.z += MathHelper::Cos(angle) * P_T.x;

	//position_ = position_ + target_;

	position_ = Vector3(
		player_->Getposition().x + 10 * player_->Getrotation().Backward().x + 5 * player_->Getrotation().Right().x, 
		player_->Getposition().y + 18, 
		player_->Getposition().z + 10 * player_->Getrotation().Backward().z + 5 * player_->Getrotation().Right().z);

	target_ = position_ + player_->Getrotation().Forward() * 50;

	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	//TPSCamera::GetInstance().Position.Set(Vector3(100,100,100));
	TPSCamera::GetInstance().Target.Set(target_);
	TPSCamera::GetInstance().Up.Set(Vector3::Up);
	TPSCamera::GetInstance().Update();

	move(position, 1.0f, 0.2f, 0.8f);
}

void Camera::draw() const
{

	Graphics3D::view_matrix(Matrix::CreateLookAt(position_,
		target_, { 0.0f,5.0f,0.0f }));
	//Graphics3D::projection_matrix(Matrix::CreatePerspectiveFieldOfView(
	//	49.0f, 640.0f / 480.0f, 0.3f, 1000.0f));

	//カメラの設定
//Graphics3D::view_matrix(Matrix::CreateLookAt(position_,
//	target_, { 0.0f,5.0f,0.0f }));
//Graphics3D::projection_matrix(Matrix::CreatePerspectiveFieldOfView(
//	49.0f, 640.0f / 480.0f, 0.3f, 1000.0f));

	DrawFormatString(600, 600, GetColor(255, 255, 255), "%f", GamePad::GetInstance().RightStick().y);
	DrawFormatString(600, 700, GetColor(255, 255, 255), "%f",angle);

	//DrawFormatString(600, 700, GetColor(255, 255, 255), "%f", m_FarPoint.x);
	//DrawFormatString(600, 800, GetColor(255, 255, 255), "%f", m_FarPoint.y);


}

void Camera::move(const Vector3 & rest_position, float stiffness, float friction, float mass)
{
	//ばねの伸び具合を計算
	const auto stretch = position_ - rest_position;
	//ばねの力を計算
	const auto force = -stiffness * stretch;
	//加速度を追加
	const auto acceleration = force / mass;
	//移動速度を計算
	velocity_ = friction * (velocity_ + acceleration);
	//座標の更新
	position_ += velocity_;
}

void Camera::PlayerInput()
{
	m_FarPoint = Vector2::Clamp(m_FarPoint, Vector2(30.0f, 20.0f), Vector2(75.0f, 60.0f));

	//m_FarPoint = m_FarPoint + GamePad::GetInstance().RightStick();
}
