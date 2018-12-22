#include "TestEnemy.h"

TestEnemy::TestEnemy(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body):
Actor(world, "Enemy", position, body),
mesh_{ model }
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());

	hp_ = 10;
}

void TestEnemy::initialize()
{
}

void TestEnemy::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());

	if (hp_ <= 0)
	{
		die();
	}
}

void TestEnemy::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();

	DrawFormatString(0, 500, GetColor(0, 255, 255), "%i", hp_);
}

void TestEnemy::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (void*)&hitdir);
}
//���b�Z�[�W���󂯎��
void TestEnemy::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_PLAYER)
	{
		hit_player(*(Vector3*)param);
	}
	if (message == EventMessage::HIT_ENEMY)
	{
		hp_ -= 1;
	}
}

void TestEnemy::hit_player(const Vector3 & dir)
{
	die();
}

