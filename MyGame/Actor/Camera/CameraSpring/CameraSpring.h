#pragma once
#include "../Math/Vector3.h"

class CameraSpring
{
public:
	static 	
		void move(
		Vector3& position,
		Vector3& velocity,
		const Vector3& rest_position, //‚Î‚Ë‚ÌÃ~ˆÊ’u
		float stiffness,                //‚Î‚Ë’è”(‚Î‚Ë‚Ì‹­‚³)
		float friction,                 //–€C—Í
		float mass                      //¿—Ê
	);

};