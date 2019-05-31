#include "RedSamuraiParam.h"

void RedSamuraiParam::initialize()
{
	mswardnum = 5;
	mswardModelNum = 14;
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

void RedSamuraiParam::SetSwardModelNum(int num)
{
	mswardModelNum = num;	
}

int RedSamuraiParam::GetSwardModelNum()
{
	return mswardModelNum;
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
