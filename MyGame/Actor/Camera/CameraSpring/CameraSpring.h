#pragma once
#include "../Math/Vector3.h"

//�J�����̃o�l
class CameraSpring
{
public:
	static 	
		void move(
		Vector3& position,
		Vector3& velocity,
		const Vector3& rest_position, //�΂˂̐Î~�ʒu
		float stiffness,                //�΂˒萔(�΂˂̋���)
		float friction,                 //���C��
		float mass                      //����
	);

};