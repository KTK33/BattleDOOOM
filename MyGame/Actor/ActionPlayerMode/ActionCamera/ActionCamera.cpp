#include "ActionCamera.h"
#include "../Input/InputInfoInc.h"
#include "../Math/Vector2.h"

#include "../Actor/Camera/CameraSpring/CameraSpring.h"
#include "../Actor/Camera/TPSCamera.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Texture/Sprite.h"

ActionCamera::ActionCamera(IWorld * world, std::weak_ptr<Actor> m_Player) :
	Actor(world, "ActionCamera", Vector3::Zero),
	m_player{ m_Player },
	player_{nullptr},
	m_Offset(-30.0f, 0.0f, 0.0f),
	m_Up(Vector3::UnitY),
	m_PitchSpeed(0.0f),
	m_YawSpeed(0.0f),
	mTargetCamera{ false }
{
}

void ActionCamera::update(float deltaTime)
{
	prevPosition_ = position_;
	//プレイヤーの検索
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	PlayerInput(deltaTime);

	//ばね
	CameraSpring::move(position_, velocity_, prevPosition_, 1.0f, 0.2f, 0.8f);
}

void ActionCamera::draw() const {
}

void ActionCamera::PlayerInput(float deltaTime)
{
	m_YawSpeed = RightStick::GetInstance().GetAngle().x;
	m_PitchSpeed = RightStick::GetInstance().GetAngle().y;

	if (world_->GetPauseCheck() == true) return;
	//ワールド上方を軸とするヨーのクォータニオンを作成
	const Quaternion yaw(Vector3::UnitY, m_YawSpeed * deltaTime);
	//カメラのオフセットと上方ベクトルをヨーで変換
	m_Offset = Quaternion::Transform(m_Offset, yaw);
	m_Up = Quaternion::Transform(m_Up, yaw);

	//カメラの前方/右方向を計算
	Vector3 forward = -1.0f * m_Offset;
	forward.Normalize();
	Vector3 right = Vector3::Cross(m_Up, forward);
	right.Normalize();

	//カメラ右方向を軸とするピッチのクォータニオンを作成
	const Quaternion pitch(right, m_PitchSpeed * deltaTime);
	//カメラのオフセットと上方ベクトルをピッチで変換
	m_Offset = Quaternion::Transform(m_Offset, pitch);
	m_Up = Quaternion::Transform(m_Up, pitch);

	if (!mTargetCamera)
	{
		//ターゲットカメラオフ時
		target_ = player_->Getposition();
		target_.y = target_.y + PlayerHeight;
		position_ = target_ + m_Offset;
	}
	else
	{
		//ターゲットカメラオン時
		//敵の検索
		auto enemy_ = world_->find_actor(ActorGroup::Enemy, "RedSamurai").get();
		if (enemy_ == nullptr) return;

		target_ = enemy_->Getposition();
		target_.y = target_.y + PlayerHeight;

		//敵→プレイヤーのベクトルの取得
		const Vector3 Target_Player_Vec = Vector3(enemy_->Getposition().x - position_.x, enemy_->Getposition().y - position_.y, enemy_->Getposition().z - position_.z).Normalize();

		//プレイヤーの座標から上記のベクトルを引く(何倍かする)
		position_ = player_->Getposition() - Target_Player_Vec * 30;
		position_.y = position_.y + PlayerHeight;

		//右方向の取得
		m_Up = Vector3::Up;
		forward = Target_Player_Vec;
		right = Vector3::Cross(m_Up, forward);
		right.Normalize();

	}

	//プレイヤーにカメラの前方向と右方向のベクトルを送信する
	m_player.lock()->receiveMessage(EventMessage::ACTION_CAMERA_FORWARD, reinterpret_cast<void*>(&forward));
	m_player.lock()->receiveMessage(EventMessage::ACTION_CAMERA_RIGHT, reinterpret_cast<void*>(&right));

	//カメラに値を設定
	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	TPSCamera::GetInstance().Target.Set(target_);
	TPSCamera::GetInstance().Up.Set(m_Up);
	TPSCamera::GetInstance().Update();
}

void ActionCamera::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::TARGET_CAMERA)
	{
		mTargetCamera =*static_cast<bool*>(param);
	}
}
