#include "EnemyMove.h"

void EnemyMove::Move(Vector3 & pos, Vector3 targetpos, float speed, bool & attack,float dis)
{

	//�v���C���[�Ƃ̋���
	const float PlayerDis = Vector3::Distance(pos, targetpos);

	//�����ɂ���čU�����������
	if (PlayerDis <= dis){
		attack = true;
	}
	else{
		attack = false;
	}

	//�v���C���[�ւ̃x�N�g��
	const Vector3 playervec = Vector3(targetpos.x - pos.x, targetpos.y - pos.y, targetpos.z - pos.z).Normalize();

	pos += playervec * speed;
}
