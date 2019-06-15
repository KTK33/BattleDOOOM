#include "BigBossEnemyParam.h"

void BigBossEnemyParam::initialize()
{
	mrota = false;
}

void BigBossEnemyParam::Set_RotaCheck(bool r)
{
	mrota = r;
}

bool BigBossEnemyParam::Get_RotaCheck()
{
	return mrota;
}