#include "EnemyAttackFire.h"

EnemyAttackFire::EnemyAttackFire(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world,"EnemyAttackFire",position,body),
	mesh_{model},
	mEnemyForward{Vector3::Zero},
	mPlyaerVector{Vector3::Zero}
{
	initialize();
}

void EnemyAttackFire::initialize()
{
	mesh_.transform(Getpose());

	player_ = world_->find_actor(ActorGroup::Player, "Player").get();

	//�v���C���[�܂ł̃x�N�g���擾
	mPlyaerVector = Vector3(player_->Getposition().x - position_.x, player_->Getposition().y - position_.y, player_->Getposition().z - position_.z);

}

void EnemyAttackFire::update(float deltaTime)
{
	mesh_.update(deltaTime);
	//�s��̐ݒ�
	mesh_.transform(Getpose());

	position_ +=mPlyaerVector * 0.01f;
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
	mEnemyForward = forward;
}

void EnemyAttackFire::collision()
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
