#include "Field.h"
#include "../Collision/BoundingSphere.h"

Field::Field(int field) :
	field_{ field }
{
}

void Field::update(float deltaTime)
{
}


void Field::draw() const
{
}

int Field::modelHandle()
{
	return 0;
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
