#include "BulletItem.h"
#include "../../Texture/Sprite.h"

BulletItem::BulletItem(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world, "EnemyAttack", position, body),
	mesh_{ model }
{
}

void BulletItem::initialize()
{
}

void BulletItem::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
}

void BulletItem::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();

	//Sprite::GetInstance().DrawBillBoard(SPRITE_ID::HP_GAUGE,position_ , Vector2::Zero, 30.0f);
}

void BulletItem::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	int gunpoint = 5;
	other.receiveMessage(EventMessage::GET_BULLET, (void*)&gunpoint);
}

void BulletItem::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_PLAYER)
	{
		die();
	}
}
