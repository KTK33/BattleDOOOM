#include "ShootingPlayerBullet.h"
#include "../World/IWorld.h"
#include "../Actor/ActorGroup.h"
#include "../Sound/Sound.h"

ShootingPlayerBullet::ShootingPlayerBullet(IWorld * world, const Vector3 & P_position, Vector3 & A_position, int AttackParam, const IBodyPtr & body):
	Actor(world, "Ball", P_position, body),
	m_GoPos{ A_position },
	Hit{false}
{
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();

	m_InitFar = Vector3(m_GoPos.x - position_.x, m_GoPos.y - position_.y, m_GoPos.z - position_.z);

	rotation_ = -player_->Getrotation();

	world_->send_message(EventMessage::DAMAGEPARAM, reinterpret_cast<void*>(&AttackParam));

	Sound::GetInstance().PlaySE(SE_ID::SHOOT_SE);
}

void ShootingPlayerBullet::initialize()
{}

void ShootingPlayerBullet::update(float deltaTime)
{
	//’e‚ÌˆÚ“®ˆ—
	position_ += m_InitFar * 0.3f;
	collision();
}

void ShootingPlayerBullet::onCollide(Actor & other)
{
	const Vector3 hitdir = position_;
	other.receiveMessage(EventMessage::HIT_BALL,(void*)&hitdir);
}

void ShootingPlayerBullet::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_ENEMY)
	{
		die();
	}
}

void ShootingPlayerBullet::collision()
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

void ShootingPlayerBullet::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}