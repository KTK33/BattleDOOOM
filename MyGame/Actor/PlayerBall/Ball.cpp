#include "Ball.h"
#include "../../World/IWorld.h"
#include "../ActorGroup.h"

Ball::Ball(IWorld* world, const Vector3& P_position, Vector3& A_position, const IBodyPtr& body):
	Actor(world,"Ball", P_position,body),
	enemy_{ nullptr },
	deadTime{20},
	m_GoPos{A_position}
{
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	enemy_ = world_->find_actor(ActorGroup::System, "Camera").get();

	m_InitFar = Vector3(m_GoPos.x - position_.x, m_GoPos.y - position_.y, m_GoPos.z - position_.z);

	rotation_ = -player_->Getrotation();

}

void Ball::initialize()
{
	Hit = false;
}

void Ball::update(float deltaTime)
{
	distance();

	//position_ = Vector3::Lerp(position_, Vector3(enemy_->Getposition().x,enemy_->Getposition().y + 10.0f,enemy_->Getposition().z),0.1f);

	deadTime--;
	if (deadTime <= 0) die();
}

void Ball::onCollide(Actor & other)
{
	Vector3 hitdir = position_;
	int DamageVal = 1;
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
void Ball::homing()
{
	//const auto& to_target = player_->pose().Translation() - position_;

	//position_ = Vector3::Lerp(position_, player_->pose().Translation(), 0.1f);
	position_ = Vector3::Lerp(Vector3(position_.x, position_.y, position_.z),
		Vector3(enemy_->Getpose().Translation().x, enemy_->Getpose().Translation().y + 10, enemy_->Getpose().Translation().z),0.1f);

	//const auto angle = MathHelper::Clamp(target_angle(), -TurnAngle, TurnAngle);
	//rotation_ *= Matrix::CreateRotationY(angle);
	////‘O‚ÉˆÚ“®‚·‚é
	//rotation_.NormalizeRotationMatrix();
	//position_ += rotation_.Forward() * m_BallSPeed * 0.5f;

}

float Ball::target_angle() const
{
	const auto& to_target = enemy_->Getpose().Translation() - position_;
	const auto angle = Vector3::Angle(rotation_.Forward(), to_target);
	const auto& forward_cross_target = Vector3::Cross(rotation_.Forward(), to_target);
	return (forward_cross_target.y >= 0.0f) ? angle : -angle;
}
