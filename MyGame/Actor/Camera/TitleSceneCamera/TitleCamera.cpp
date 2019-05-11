#include "TitleCamera.h"
#include "../TPSCamera.h"

TitleCamera::TitleCamera(IWorld * world, std::weak_ptr<Actor> m_Player):
	Actor(world,"TitleCamera",Vector3::Zero),
	m_player{m_Player},
	bullet{nullptr},
	cameraBack{4}
{
	target_ = Vector3(m_player.lock()->Getposition().x, 
		m_player.lock()->Getposition().y + 16, 
		m_player.lock()->Getposition().z
		);

	position_ = Vector3(
		m_player.lock()->Getposition().x + 10 * m_player.lock()->Getrotation().Forward().x + 4 * m_player.lock()->Getrotation().Right().x,
		m_player.lock()->Getposition().y + 16,
		m_player.lock()->Getposition().z + 10 * m_player.lock()->Getrotation().Forward().z + 4 * m_player.lock()->Getrotation().Right().z);
}

void TitleCamera::update(float deltaTime)
{
	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	TPSCamera::GetInstance().Target.Set(target_);
	TPSCamera::GetInstance().Up.Set(Vector3::Up);
	TPSCamera::GetInstance().Update();

	move(position_, 1.0f, 0.2f, 0.8f);

	if (world_->find_actor(ActorGroup::Ball, "TitleBullet") == NULL)
	{
		return;
	}
	else
	{
		bullet = world_->find_actor(ActorGroup::Ball, "TitleBullet").get();
		target_ = bullet->Getposition();
	}

	//CameraMove();
}

void TitleCamera::draw() const
{
}

void TitleCamera::move(const Vector3 & rest_position, float stiffness, float friction, float mass)
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

void TitleCamera::CameraMove()
{
	cameraBack = min(cameraBack + 0.5f, 10);
}
