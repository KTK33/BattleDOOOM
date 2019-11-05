#pragma once
#include "../Math/MathH.h"

//èdóÕ
class Gravity
{
public:
	void gravity(Vector3 & pos, Vector3 & vel, bool floor);

private:
	float gravityVal{ 9.8f * 0.1f };
};