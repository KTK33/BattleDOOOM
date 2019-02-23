#include "Field.h"
#include "../Collision/BoundingSphere.h"

Field::Field(int field) :
	field_{ field }
{
	//モデルが設定されていなかったら返す
	if (field_ < 0) return;

	// フィールドの座標指定
	MV1SetPosition(field_, Vector3::Zero);
	// フィールドの拡大率指定
	MV1SetScale(field_, Vector3::Vector3ToVECTOR(Vector3::One * 1.0f));


}

void Field::update(float deltaTime)
{
}


void Field::draw() const
{
	MV1DrawModel(field_);
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
