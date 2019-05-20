#include "EnemyMove.h"

void EnemyMove::Move(Vector3 & pos, Vector3 targetpos, float speed, bool & attack,float dis)
{

	//プレイヤーとの距離
	const float PlayerDis = Vector3::Distance(pos, targetpos);

	//距離によって攻撃判定をする
	if (PlayerDis <= dis){
		attack = true;
	}
	else{
		attack = false;
	}

	//プレイヤーへのベクトル
	const Vector3 playervec = Vector3(targetpos.x - pos.x, targetpos.y - pos.y, targetpos.z - pos.z).Normalize();

	pos += playervec * speed;
}
