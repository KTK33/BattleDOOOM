#include "SelectCamera.h"
#include "../TPSCamera.h"

SelectCamera::SelectCamera(IWorld * world, std::weak_ptr<Actor> m_Player):
	Actor(world, "SelectCamera", Vector3::Zero),
	m_player{ m_Player }
{
	target_ = m_player.lock()->Getposition() + m_player.lock()->Getpose().Left() * 20.0f;
	target_.y += 15.0f;

	position_ = m_player.lock()->Getposition() + m_player.lock()->Getpose().Forward() * 30.0f;

	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	TPSCamera::GetInstance().Target.Set(target_);
	TPSCamera::GetInstance().Up.Set(Vector3::Up);
	TPSCamera::GetInstance().Update();
}