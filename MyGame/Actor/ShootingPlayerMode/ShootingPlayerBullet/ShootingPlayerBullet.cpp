#include "ShootingPlayerBullet.h"
#include "../World/IWorld.h"
#include "../Actor/ActorGroup.h"
#include "../Sound/Sound.h"
#include "../Actor/CommonUIActor/Effect2D/Effect2D.h"

ShootingPlayerBullet::ShootingPlayerBullet(IWorld * world, const Vector3 & P_position, Vector3 & A_position, int AttackParam, const IBodyPtr & body):
	Actor(world, "Ball", P_position, body),
	mesh_{ 5 },
	m_GoPos{ A_position },
	Hit{false}
{
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();

	m_InitFar = Vector3(m_GoPos.x - position_.x, m_GoPos.y - position_.y, m_GoPos.z - position_.z).Normalize();

	rotation_ = Matrix::Invert(Matrix::CreateLookAt(player_->Getposition(), player_->Getposition() + player_->Getpose().Forward(), Vector3::Up)) * Matrix::CreateRotationY(200);

	world_->send_message(EventMessage::DAMAGEPARAM, reinterpret_cast<void*>(&AttackParam));

	Sound::GetInstance().PlaySE(SE_ID::SHOOT_SE);
}

void ShootingPlayerBullet::initialize()
{
	mesh_.transform(Getpose());
}

void ShootingPlayerBullet::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	//’e‚ÌˆÚ“®ˆ—
	position_ += m_InitFar * 5.0f;
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
		world_->add_actor(ActorGroup::Effect, new_actor<Effect2D>(world_, position_, EffectSize(), SPRITE_ID::EFFECT_BULLETHIT));
		die();
	}
}

void ShootingPlayerBullet::collision()
{
	//‚Ô‚Â‚©‚Á‚½‚©
	Vector3 result;
	//•Ç‚Æ‚Ô‚Â‚¯‚Ä‚©‚ç
	if (field(result)) {
		world_->add_actor(ActorGroup::Effect, new_actor<Effect2D>(world_, position_, EffectSize(), SPRITE_ID::EFFECT_BULLETHIT));
		die();
	}

	//°‚Æ‚ÌÚ’n”»’è
	if (floor(result)) {
		world_->add_actor(ActorGroup::Effect, new_actor<Effect2D>(world_, position_, EffectSize(), SPRITE_ID::EFFECT_BULLETHIT));
		die();
	}
}

float ShootingPlayerBullet::EffectSize()
{
	auto player = world_->find_actor(ActorGroup::Player, "Player").get();
	float dis = Vector3::Distance(player->Getposition(), position_);
	float size = 0.0f;
	if (dis <= 15.0f) size = 1.2f;
	else if (dis <= 100.0f) size = 1.15f;
	else if (dis <= 300.0f) size = 1.1f;
	else dis = 1.0f;

	return size;
}

void ShootingPlayerBullet::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}