#include "Camera.h"
#include "../../Graphics/Graphics3D.h"

#include "../../Input/GamePad.h"
#include "../../Math/Vector2.h"

#include "TPSCamera.h"
#include "../../Scene/GameData/GameDataManager.h"
#include "../../Texture/Sprite.h"
#include "../UIActor/PlaySceneUI/GameOverUI.h"

Camera::Camera(IWorld * world, std::weak_ptr<Actor> m_Player) :
	Actor(world, "Camera", Vector3::Zero),
	AimPosMove{ 0,0 },
	m_player{m_Player},
	alreadyGO{false},
	AHUAH{1}
{
}

void Camera::update(float deltaTime)
{
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
	//const auto position = Vector3{ 0.0f,m_FarPoint.x,m_FarPoint.y }*player_->Getpose();
	//target_ = player_->Getposition(); /*+Vector3{ 0.0f,10.0f,0.0f }*/;
	//target_ = player_->Getposition() + player_->Getrotation().Forward() *5;

	if (GameDataManager::getInstance().GetPlayerDead() == true)
	{
		PlayerGameOver();
	}
	else
	{
		PlayerInput();
	}

	//position_.x += GamePad::GetInstance().RightStick().x * 10;
	//position_.z += GamePad::GetInstance().RightStick().x * 10;

	//Vector3 P_T = Vector3::Distance(position_, target_);
	//P_T = Vector3::Clamp(P_T, Vector3(0, 0, 0), Vector3(10, 10, 10));

	//Vector3 fw = Vector3::CreateFromYawPitch(XX, target_.x);

	//angle += XX;
	//position_.x += MathHelper::Sin(angle) * P_T.x;
	//position_.z += MathHelper::Cos(angle) * P_T.x;

	//position_ = position_ + target_;


	move(position_, 1.0f, 0.2f, 0.8f);

	if (CheckHitKey(KEY_INPUT_U))
	{
		AHUAH += 0.0005f;
	}

	if (CheckHitKey(KEY_INPUT_I	))
	{
		AHUAH -= 0.0005f;
	}


}

void Camera::draw() const
{

	//Graphics3D::view_matrix(Matrix::CreateLookAt(position_,
	//	target_, { 0.0f,5.0f,0.0f }));
	//Graphics3D::projection_matrix(Matrix::CreatePerspectiveFieldOfView(
	//	49.0f, 640.0f / 480.0f, 0.3f, 1000.0f));

	//カメラの設定
//Graphics3D::view_matrix(Matrix::CreateLookAt(position_,
//	target_, { 0.0f,5.0f,0.0f }));
//Graphics3D::projection_matrix(Matrix::CreatePerspectiveFieldOfView(
//	49.0f, 640.0f / 480.0f, 0.3f, 1000.0f));

//	DrawFormatString(500, 500, GetColor(255, 255, 255), "%f", AimPosMove.x);
//DrawFormatString(700, 500, GetColor(255, 255, 255), "%f", AimPosMove.y);
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
	target_ = position_ + player_->Getrotation().Forward() * 50;

	position_ = Vector3(
		player_->Getposition().x + 10 * player_->Getrotation().Backward().x + 5 * player_->Getrotation().Right().x,
		player_->Getposition().y + 18,
		player_->Getposition().z + 10 * player_->Getrotation().Backward().z + 5 * player_->Getrotation().Right().z);

	if (world_->GetPauseCheck() == false && GameDataManager::getInstance().GetItemBoxOpen() == false)
	{
		if (GameDataManager::getInstance().GetSightCheck() == true)
		{
			AimPosMove += GamePad::GetInstance().RightStick() * (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
		}
		else
		{
			AimPosMove += GamePad::GetInstance().RightStick() * (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
		}
	}

	target_.x += player_->Getrotation().Right().x * AimPosMove.x;
	target_.y += AimPosMove.y;
	target_.z += player_->Getrotation().Right().z * AimPosMove.x;

	if (GameDataManager::getInstance().GetSightCheck() == true)
	{
		position_ = Vector3(
			player_->Getposition().x + 4 * player_->Getrotation().Backward().x + 2.5f * player_->Getrotation().Right().x,
			player_->Getposition().y + 16,
			player_->Getposition().z + 4 * player_->Getrotation().Backward().z + 2.5f * player_->Getrotation().Right().z);

		target_ = Vector3::Lerp(target_, position_ + player_->Getrotation().Forward() * 1, 0.1f);

		m_player.lock()->receiveMessage(EventMessage::SIGHT_POSITION, (void*)&target_);

		float XX = 0;
		XX = GamePad::GetInstance().RightStick().x * (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
		m_player.lock()->receiveMessage(EventMessage::SIGHT_ROTATION, (void*)&XX);

		AimPosMove = Vector2::Clamp(AimPosMove, Vector2(15, -15), Vector2(30, 0));

	}
	else
	{
		position_ = Vector3(
			player_->Getposition().x + 10 * player_->Getrotation().Backward().x + 5 * player_->Getrotation().Right().x,
			player_->Getposition().y + 18,
			player_->Getposition().z + 10 * player_->Getrotation().Backward().z + 5 * player_->Getrotation().Right().z);

		target_ = Vector3::Lerp(target_, position_ + player_->Getrotation().Forward(), 0.1f);
		AimPosMove = Vector2::Clamp(AimPosMove, Vector2(0, -30), Vector2(0, 30));
	}

	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	TPSCamera::GetInstance().Target.Set(target_);
	TPSCamera::GetInstance().Up.Set(Vector3::Up);
	TPSCamera::GetInstance().Update();

}

void Camera::PlayerGameOver()
{
	position_ = Vector3(
		player_->Getposition().x + DeadCamera.x * player_->Getrotation().Forward().x + 1 * player_->Getrotation().Right().x,
		player_->Getposition().y + DeadCamera.y,
		player_->Getposition().z + DeadCamera.z * player_->Getrotation().Forward().z + 1 * player_->Getrotation().Right().z);

	target_ = player_->Getposition() + 10 * player_->Getrotation().Forward();

	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	TPSCamera::GetInstance().Target.Set(target_);
	TPSCamera::GetInstance().Up.Set(Vector3::Up);
	TPSCamera::GetInstance().Update();

	if (GameDataManager::getInstance().GetPlayerDead() == true)
	{
		DeadCamera += Vector3::One * 0.25f;
	}

	DeadCamera = Vector3::Clamp(DeadCamera, Vector3::Zero, Vector3(100,100,100));

	if (!alreadyGO)
	{
		world_->add_actor(ActorGroup::GameOverUI, new_actor<GameOverUI>(world_));
		alreadyGO = true;
	}
}
