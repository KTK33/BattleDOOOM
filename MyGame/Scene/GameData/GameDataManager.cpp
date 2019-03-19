#include "GameDataManager.h"

void GameDataManager::initialize()
{
	TitleCheck = false;
	DeadBossEnemyCheck = false;
	DeadPlayerCheck = false;
	SightCheck = false;

	BGMVAL = 5;
	SE_VAL = 5;
	AIM_SPD = 5;
}

void GameDataManager::update()
{
}

void GameDataManager::SetTitleCheck(bool Stc)
{
	TitleCheck = Stc;
}

bool GameDataManager::GetTitleCheck()
{
	return TitleCheck;
}

void GameDataManager::SetDeadBossEnemy(bool db)
{
	DeadBossEnemyCheck = db;
}

bool GameDataManager::GetDeadBossEnemy()
{
	return DeadBossEnemyCheck;
}

void GameDataManager::SetPlayerDead(bool pd)
{
	DeadPlayerCheck = pd;
}

bool GameDataManager::GetPlayerDead()
{
	return DeadPlayerCheck;
}

void GameDataManager::SetItemBoXOpen(bool IBX)
{
	ItemBoxOpne = IBX;
}

bool GameDataManager::GetItemBoxOpen()
{
	return ItemBoxOpne;
}

void GameDataManager::SetSightCheck(bool SC)
{
	SightCheck = SC;
}

bool GameDataManager::GetSightCheck()
{
	return SightCheck;
}

void GameDataManager::SetBGMVAL(int BGM)
{
	BGMVAL = BGM;
}

int GameDataManager::GetBGMVAL()
{
	return BGMVAL;
}

void GameDataManager::SetSEVAL(int SE)
{
	SE_VAL = SE;
}

int GameDataManager::GetSEVAL()
{
	return SE_VAL;
}

void GameDataManager::SetAIMSPD(int AIM)
{
	AIM_SPD = AIM;
}

int GameDataManager::GetAIMSPD()
{
	return AIM_SPD;
}
