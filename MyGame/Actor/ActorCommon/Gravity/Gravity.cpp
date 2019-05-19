#include "Gravity.h"

void Gravity::gravity(Vector3 & pos, Vector3 & vel, bool floor)
{
	//d—Íˆ—
	//velocity_ = Vector3::Zero;
	vel += Vector3::Up * -gravityVal;
	pos += vel;

	vel *= 0.8f;
	if (vel.Length() < 0.01f) {
		vel = 0.0f;
	}

	if (floor) gravityVal = 0.0f;
	else gravityVal = 9.8f*0.1f;
}
