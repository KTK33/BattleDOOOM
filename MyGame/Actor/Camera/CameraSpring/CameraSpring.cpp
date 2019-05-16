#include "CameraSpring.h"

void CameraSpring::move(Vector3 & position, Vector3 & velocity, const Vector3 & rest_position, float stiffness, float friction, float mass)
{
	//�΂˂̐L�ы���v�Z
	const auto stretch = position - rest_position;
	//�΂˂̗͂��v�Z
	const auto force = -stiffness * stretch;
	//�����x��ǉ�
	const auto acceleration = force / mass;
	//�ړ����x���v�Z
	velocity = friction * (velocity + acceleration);
	//���W�̍X�V
	position += velocity;
}
