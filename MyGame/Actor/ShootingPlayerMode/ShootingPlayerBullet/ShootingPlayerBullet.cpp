#include "ShootingPlayerBullet.h"
#include "../World/IWorld.h"
#include "../Actor/ActorGroup.h"
#include "../Sound/Sound.h"

ShootingPlayerBullet::ShootingPlayerBullet(IWorld * world, const Vector3 & P_position, Vector3 & A_position, int AttackParam, const IBodyPtr & body):
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

void ShootingPlayerBullet::initialize()
{}

void ShootingPlayerBullet::update(float deltaTime)
{
	//���̈ړ�����
	distance();

	//�Ǐ��Ƃ̓����蔻��
	collision();

	//deadTime--;
	//if (deadTime <= 0) die();
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
	//�Ԃ�������
	Vector3 result;
	//�ǂƂԂ��Ă���
	if (field(result)) {
		die();
	}

	//���Ƃ̐ڒn����
	if (floor(result)) {
		die();
	}
}

void ShootingPlayerBullet::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();

}
void ShootingPlayerBullet::distance()
{
	position_ += m_InitFar * 0.3f;
}

float ShootingPlayerBullet::target_angle() const
{
	const auto to_target = enemy_->Getpose().Translation() - position_;
	const auto angle = Vector3::Angle(rotation_.Forward(), to_target);
	const auto forward_cross_target = Vector3::Cross(rotation_.Forward(), to_target);
	return (forward_cross_target.y >= 0.0f) ? angle : -angle;
}
