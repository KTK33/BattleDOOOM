#pragma once

#include "../Math/Vector2.h"

class LeftStick
{
private:
	LeftStick() {}
	~LeftStick() = default;
public:
	static LeftStick &GetInstance() {
		static LeftStick g;
		return g;
	}

	Vector2 GetAngle();

	bool KnockCheck();
};
