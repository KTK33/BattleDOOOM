#pragma once
#include "../Math/Vector3.h"

//カメラのバネ
class CameraSpring
{
public:
	static 	
		void move(
		Vector3& position,
		Vector3& velocity,
		const Vector3& rest_position, //ばねの静止位置
		float stiffness,                //ばね定数(ばねの強さ)
		float friction,                 //摩擦力
		float mass                      //質量
	);

};