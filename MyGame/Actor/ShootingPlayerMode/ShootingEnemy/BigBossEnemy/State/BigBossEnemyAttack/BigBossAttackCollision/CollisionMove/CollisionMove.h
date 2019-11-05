#pragma once
#include "../Math/MathH.h"

//大ボスの攻撃の位置、向き、時間設定クラス
class CollisionMove
{
public:
	//直線攻撃
	void Move1(Vector3 & pos, Matrix & rote, int time);

	//範囲(小)攻撃
	void Move2(Vector3 & pos, Matrix & rote, int time);

	//溜め攻撃
	void Move3(Vector3 & pos, Matrix & rote, int time);

	//範囲(大)攻撃
	void Move4(Vector3 & pos, Matrix & rote, int time);

};