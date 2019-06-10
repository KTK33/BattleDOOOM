#include "BigBossEnemyParam.h"

void BigBossEnemyParam::initialize()
{
	mstate = ActorStateID::NONE;
	mhp = 0;
}

void BigBossEnemyParam::SetPlayerState(ActorStateID id)
{
	mstate = id;
}

ActorStateID BigBossEnemyParam::GetPlayerState()
{
	return mstate;
}

void BigBossEnemyParam::SetPlayerHP(int hp)
{
	mhp = hp;
}

int BigBossEnemyParam::GetPlayerHP()
{
	return mhp;
}
