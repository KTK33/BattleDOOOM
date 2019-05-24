#include "TitleCamera.h"
#include "../TPSCamera.h"
#include "../Actor/Camera/CameraSpring/CameraSpring.h"

TitleCamera::TitleCamera(IWorld * world, std::weak_ptr<Actor> m_Player):
	Actor(world,"TitleCamera",Vector3::Zero),
	m_player{m_Player},
	bullet{nullptr}
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

	//‚Î‚Ë
	CameraSpring::move(position_, velocity_, position_, 1.0f, 0.2f, 0.8f);

	if (world_->find_actor(ActorGroup::Ball, "TitleBullet") == NULL)
	{
		return;
	}
	else
	{
		bullet = world_->find_actor(ActorGroup::Ball, "TitleBullet").get();
		target_ = bullet->Getposition();
	}
}