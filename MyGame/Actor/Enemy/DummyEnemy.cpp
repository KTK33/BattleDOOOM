#include "DummyEnemy.h"
#include "../../Scene/GameData/GameDataManager.h"

DummyEnemy::DummyEnemy(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body) :
	Actor(world, "DummyEnemy", position, body),
	mesh_{ model }
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());

	hp_ = 1;
}

void DummyEnemy::initialize()
{
}

void DummyEnemy::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());

	if (hp_ <= 0)
	{
		deadAction();
	}
}

void DummyEnemy::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}

void DummyEnemy::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (void*)&hitdir);
}
//メッセージを受け取る
void DummyEnemy::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_PLAYER)
	{
		hit_player(*(Vector3*)param);
	}
	if (message == EventMessage::HIT_BALL)
	{
		hp_ -= 1;
	}
	if (message == EventMessage::DEAD_DUMMY_ENEMY){
		die();
	}
}

void DummyEnemy::hit_player(const Vector3 & dir)
{
	die();
}

void DummyEnemy::deadAction()
{
	world_->send_message(EventMessage::DUMMY_DEAD_ENEMY, nullptr);
	die();

}

