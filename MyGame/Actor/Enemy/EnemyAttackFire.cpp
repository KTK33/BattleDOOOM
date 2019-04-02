#include "EnemyAttackFire.h"

EnemyAttackFire::EnemyAttackFire(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world,"EnemyAttackFire",position,body),
	mesh_{model},
	EnemyForward{Vector3::Zero},
	plyaerVector{Vector3::Zero}
{
	mesh_.transform(Getpose());

	player_ = world_->find_actor(ActorGroup::Player, "Player").get();

	plyaerVector = Vector3(player_->Getposition().x - position_.x, player_->Getposition().y - position_.y, player_->Getposition().z - position_.z);
}

void EnemyAttackFire::initialize()
{
}

void EnemyAttackFire::update(float deltaTime)
{
	mesh_.update(deltaTime);
	//s—ñ‚ÌÝ’è
	mesh_.transform(Getpose());

	//if (Vector3::Distance(position_, player_->Getposition()) >= 30)
	//{
	//	position_ += plyaerVector * 0.1f;
	//}

	position_ += plyaerVector * 0.01f;

	DeadTimer++;
	if (DeadTimer >= 120) die();
}

void EnemyAttackFire::onCollide(Actor & other)
{
	int DamageVal = 2;
	other.receiveMessage(EventMessage::HIT_ENEMY_BULLET, (void*)&DamageVal);
}

void EnemyAttackFire::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_BALL){
		die();
	}
}

void EnemyAttackFire::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}

void EnemyAttackFire::GetEnemyForward(Vector3 forward)
{
	EnemyForward = forward;
}
