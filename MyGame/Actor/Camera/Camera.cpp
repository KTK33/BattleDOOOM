#include "Camera.h"
#include "../../Graphics/Graphics3D.h"

#include "../../Input/GamePad.h"
#include "../../Input/Keyboard.h"
#include "../../Math/Vector2.h"

#include "TPSCamera.h"
#include "../../Scene/GameData/GameDataManager.h"
#include "../../Texture/Sprite.h"
#include "../UIActor/PlaySceneUI/GameOverUI.h"
#include "../UIActor/PlaySceneUI/GameClearUIh.h"

Camera::Camera(IWorld * world, std::weak_ptr<Actor> m_Player) :
	Actor(world, "Camera", Vector3::Zero),
	AimPosMove{ 0,0 },
	m_player{m_Player},
	alreadyGO{false}
{
}

void Camera::update(float deltaTime)
{
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	if (GameDataManager::getInstance().GetPlayerDead() == true || 
		GameDataManager::getInstance().GetDeadBossEnemy() == true)
	{
		PlayerGameFinish();
	}
	else
	{
		PlayerInput();
	}

	move(position_, 1.0f, 0.2f, 0.8f);
}

void Camera::draw() const{}

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
	target_ = position_ + player_->Getrotation().Forward() * 50;

	position_ = Vector3(
		player_->Getposition().x + 10 * player_->Getrotation().Backward().x + 5 * player_->Getrotation().Right().x,
		player_->Getposition().y + 18,
		player_->Getposition().z + 10 * player_->Getrotation().Backward().z + 5 * player_->Getrotation().Right().z);

	if (world_->GetPauseCheck() == false && GameDataManager::getInstance().GetItemBoxOpen() == false)
	{
		if (GameDataManager::getInstance().GetSightCheck() == true)
		{
			if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
			{
				AimPosMove.y += 1.0f * (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
			}
			if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
			{
				AimPosMove.y -= 1.0f* (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
			}
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
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT)){
			XX = 1.0f* (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
		}
		else if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT)){
			XX = -1.0f * (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
		}
		else{
			XX = GamePad::GetInstance().RightStick().x * (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
		}
		m_player.lock()->receiveMessage(EventMessage::SIGHT_ROTATION, (void*)&XX);

		AimPosMove = Vector2::Clamp(AimPosMove, Vector2(15, -20), Vector2(15, 15));

	}
	else
	{
		position_ = Vector3(
			player_->Getposition().x + 10 * player_->Getrotation().Backward().x + 5 * player_->Getrotation().Right().x,
			player_->Getposition().y + 18,
			player_->Getposition().z + 10 * player_->Getrotation().Backward().z + 5 * player_->Getrotation().Right().z);

		//position_ = Vector3::Lerp(position_, Sposition_, 0.1f);

		target_ = Vector3::Lerp(target_, position_ + player_->Getrotation().Forward(), 0.1f);
		AimPosMove = Vector2::Clamp(AimPosMove, Vector2(0, -30), Vector2(0, 30));
	}

	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	TPSCamera::GetInstance().Target.Set(target_);
	TPSCamera::GetInstance().Up.Set(Vector3::Up);
	TPSCamera::GetInstance().Update();

}

void Camera::PlayerGameFinish()
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

		DeadCamera = Vector3::Clamp(DeadCamera, Vector3::Zero, Vector3(100, 100, 100));

		if (!alreadyGO)
		{
			world_->add_actor(ActorGroup::GameFinishUI, new_actor<GameOverUI>(world_));
			alreadyGO = true;
		}

	}
	else if (GameDataManager::getInstance().GetDeadBossEnemy() == true)
	{
		DeadCamera += Vector3::One * 0.25f;

		DeadCamera = Vector3::Clamp(DeadCamera, Vector3::Zero, Vector3(100, 100, 100));

		if (!alreadyGO)
		{
			world_->add_actor(ActorGroup::GameFinishUI, new_actor<GameClearUI>(world_));
			alreadyGO = true;
		}
	}
}
