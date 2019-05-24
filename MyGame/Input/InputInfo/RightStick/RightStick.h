#pragma once

#include "../Math/Vector2.h"

class RightStick
{
private:
	RightStick() {}
	~RightStick() = default;
public:
	static RightStick &GetInstance() {
		static RightStick g;
		return g;
	}

	Vector2 GetAngle();
};
