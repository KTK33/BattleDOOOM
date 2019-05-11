#include "PlayerBullet.h"
#include "../../World/IWorld.h"
#include "../ActorGroup.h"
#include "../Sound/Sound.h"

PlayerBullet::PlayerBullet(IWorld * world, const Vector3 & P_position, Vector3 & A_position, int AttackParam, const IBodyPtr & body):
	Actor(world, "Ball", P_position, body),
	enemy_{ nullptr },
	deadTime{ 20 },
	m_GoPos{ A_position },
	Hit{false}
{
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	enemy_ = world_->find_actor(ActorGroup::System, "Camera").get();

	m_InitFar = Vector3(m_GoPos.x - position_.x, m_GoPos.y - position_.y, m_GoPos.z - position_.z);

	rotation_ = -player_->Getrotation();

	world_->send_message(EventMessage::DAMAGEPARAM, reinterpret_cast<void*>(&AttackParam));

	Sound::GetInstance().PlaySE(SE_ID::SHOOT_SE);
}

void PlayerBullet::initialize()
{}

void PlayerBullet::update(float deltaTime)
{
	//‹…‚ÌˆÚ“®ˆ—
	distance();

	//•Ç°‚Æ‚Ì“–‚½‚è”»’è
	collision();

	//deadTime--;
	//if (deadTime <= 0) die();
}

void PlayerBullet::onCollide(Actor & other)
{
	const Vector3 hitdir = position_;
	other.receiveMessage(EventMessage::HIT_BALL,(void*)&hitdir);
}

void PlayerBullet::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_ENEMY)
	{
		die();
	}
}

void PlayerBullet::collision()
{
	//‚Ô‚Â‚©‚Á‚½‚©
	Vector3 result;
	//•Ç‚Æ‚Ô‚Â‚¯‚Ä‚©‚ç
	if (field(result)) {
		die();
	}

	//°‚Æ‚ÌÚ’n”»’è
	if (floor(result)) {
		die();
	}
}

void PlayerBullet::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();

}
void PlayerBullet::distance()
{
	position_ += m_InitFar * 0.3f;
}

float PlayerBullet::target_angle() const
{
	const auto to_target = enemy_->Getpose().Translation() - position_;
	const auto angle = Vector3::Angle(rotation_.Forward(), to_target);
	const auto forward_cross_target = Vector3::Cross(rotation_.Forward(), to_target);
	return (forward_cross_target.y >= 0.0f) ? angle : -angle;
}
