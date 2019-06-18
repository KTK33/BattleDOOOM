#include "EnemyAttackFire.h"
#include "../Game/GameData/ShootingMode/ShootingBossEnemyData.h"

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

	//プレイヤーまでのベクトル取得
	mPlyaerVector = Vector3(player_->Getposition().x - position_.x, player_->Getposition().y - position_.y, player_->Getposition().z - position_.z);

}

void EnemyAttackFire::update(float deltaTime)
{
	mesh_.update(deltaTime);
	//行列の設定
	mesh_.transform(Getpose());

	position_ +=mPlyaerVector * FireSpeed;
}

void EnemyAttackFire::onCollide(Actor & other)
{
	other.receiveMessage(EventMessage::HIT_ENEMY_BULLET, (void*)&FireAttackVal);
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
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		die();
	}

	//床との接地判定
	if (floor(result)) {
		die();
	}
}
