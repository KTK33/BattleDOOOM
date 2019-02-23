#include "Field.h"
#include "../Collision/BoundingSphere.h"

Field::Field(int field) :
	field_{ field }
{
	//���f�����ݒ肳��Ă��Ȃ�������Ԃ�
	if (field_ < 0) return;

	// �t�B�[���h�̍��W�w��
	MV1SetPosition(field_, Vector3::Zero);
	// �t�B�[���h�̊g�嗦�w��
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
