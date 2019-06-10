#pragma once
#include "../Math/MathH.h"
class CollisionMove
{
public:
	//’¼üUŒ‚
	void Move1(Vector3 & pos, Matrix & rote, int time);

	//”ÍˆÍ(¬)UŒ‚
	void Move2(Vector3 & pos, Matrix & rote, int time);

	//—­‚ßUŒ‚
	void Move3(Vector3 & pos, Matrix & rote, int time);

	//”ÍˆÍ(‘å)UŒ‚
	void Move4(Vector3 & pos, Matrix & rote, int time);

};