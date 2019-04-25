#include "ActionCamera.h"
#include "../../../Input/GamePad.h"
#include "../../../Input/Keyboard.h"
#include "../../../Math/Vector2.h"

#include "../TPSCamera.h"
#include "../../../Scene/GameData/GameDataManager.h"
#include "../../../Texture/Sprite.h"

ActionCamera::ActionCamera(IWorld * world, std::weak_ptr<Actor> m_Player) :
	Actor(world, "Camera", Vector3::Zero)
	, m_Offset(-30.0f, 0.0f, 0.0f)
	, m_Up(Vector3::UnitY)
	, m_PitchSpeed(0.0f)
	, m_YawSpeed(0.0f)
{
}

void ActionCamera::update(float deltaTime)
{
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	PlayerInput(deltaTime);

	move(position_, 1.0f, 0.2f, 0.8f);
}

void ActionCamera::draw() const {}

void ActionCamera::move(const Vector3 & rest_position, float stiffness, float friction, float mass)
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

void ActionCamera::PlayerInput(float deltaTime)
{
	//カメラの操作
	m_PitchSpeed = GamePad::GetInstance().RightStick().y;
	m_YawSpeed = GamePad::GetInstance().RightStick().x;

	//ワールド上方を軸とするヨーのクォータニオンを作成
	Quaternion yaw(Vector3::UnitY, m_YawSpeed * deltaTime);
	//カメラのオフセットと上方ベクトルをヨーで変換
	m_Offset = Quaternion::Transform(m_Offset, yaw);
	m_Up = Quaternion::Transform(m_Up, yaw);

	//カメラの前方/右方向を計算
	Vector3 forward = -1.0f * m_Offset;
	forward.Normalize();
	Vector3 right = Vector3::Cross(m_Up, forward);
	right.Normalize();

	//カメラ右方向を軸とするピッチのクォータニオンを作成
	Quaternion pitch(right, m_PitchSpeed * deltaTime);
	//カメラのオフセットと上方ベクトルをピッチで変換
	m_Offset = Quaternion::Transform(m_Offset, pitch);
	m_Up = Quaternion::Transform(m_Up, pitch);

	target_ = player_->Getposition();
	position_ = target_ + m_Offset;

	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	TPSCamera::GetInstance().Target.Set(target_);
	TPSCamera::GetInstance().Up.Set(Vector3::Up);
	TPSCamera::GetInstance().Update();
}