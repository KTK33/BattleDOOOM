#include "RedSamuraiParam.h"

void RedSamuraiParam::initialize()
{
	mswardnum = 38;
	mstate = ActorStateID::NONE;
	mstop = false;
}

void RedSamuraiParam::SetSwardPosNum(int num)
{
	mswardnum = num;
}

int RedSamuraiParam::GetSwardPosNum()
{
	return mswardnum;
}

void RedSamuraiParam::SetPlayerState(ActorStateID id)
{
	mstate = id;
}

ActorStateID RedSamuraiParam::GetPlayerState()
{
	return mstate;
}

void RedSamuraiParam::SetRedSamuraiStop(bool s)
{
	mstop = s;
}

bool RedSamuraiParam::GetRedSamuraiStop()
{
	return mstop;
}
