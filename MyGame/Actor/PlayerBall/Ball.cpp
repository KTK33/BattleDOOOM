#include "Ball.h"
#include "../../World/IWorld.h"
#include "../ActorGroup.h"
#include "../Sound/Sound.h"

Ball::Ball(IWorld * world, const Vector3 & P_position, Vector3 & A_position, int AttackParam, const IBodyPtr & body):
	Actor(world, "Ball", P_position, body),
	enemy_{ nullptr },
	deadTime{ 20 },
	m_GoPos{ A_position }
{
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	enemy_ = world_->find_actor(ActorGroup::System, "Camera").get();

	m_InitFar = Vector3(m_GoPos.x - position_.x, m_GoPos.y - position_.y, m_GoPos.z - position_.z);

	rotation_ = -player_->Getrotation();

	world_->send_message(EventMessage::DAMAGEPARAM, (void*)&AttackParam);

	Sound::GetInstance().PlaySE(SE_ID::SHOOT_SE);
}

void Ball::initialize()
{
	Hit = false;
}

void Ball::update(float deltaTime)
{
	distance();

	deadTime--;
	if (deadTime <= 0) die();
}

void Ball::onCollide(Actor & other)
{
	Vector3 hitdir = position_;
	other.receiveMessage(EventMessage::HIT_BALL,(void*)&hitdir);
}

void Ball::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_ENEMY)
	{
		die();
	}
}

void Ball::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();

}
void Ball::distance()
{
	position_ += m_InitFar * 0.3f;
}

float Ball::target_angle() const
{
	const auto& to_target = enemy_->Getpose().Translation() - position_;
	const auto angle = Vector3::Angle(rotation_.Forward(), to_target);
	const auto& forward_cross_target = Vector3::Cross(rotation_.Forward(), to_target);
	return (forward_cross_target.y >= 0.0f) ? angle : -angle;
}
