#pragma once
#include "../Math/Vector3.h"

class EnemyMove
{
public:
	void Move(Vector3 & pos, Vector3 targetpos,float speed,bool & attack,float dis);
};