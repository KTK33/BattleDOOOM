#include "Field.h"
#include "../Collision/BoundingSphere.h"

Field::Field(int field) :
	field_{ field }
{
	//���f�����ݒ肳��Ă��Ȃ�������Ԃ�
	if (field_ < 0) return;
}

void Field::update(float deltaTime)
{
}


void Field::draw() const
{
}

int Field::modelHandle()
{
	return field_;
}

CollisionMesh & Field::getMesh()
{
	return mesh_;
}

int Field::getWidth() const
{
	return 0;
}

int Field::getHeight() const
{
	return 0;
}
