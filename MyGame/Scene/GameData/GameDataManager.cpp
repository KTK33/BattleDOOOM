#include "GameDataManager.h"

void GameDataManager::initialize()
{
	TitleCheck = false;
	StartCheck = false;
	DeadBossEnemyCheck = false;
	DeadPlayerCheck = false;
	SightCheck = false;
	SceneNumber = 0;
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

void GameDataManager::SetPlayerStart(bool Sps)
{
	StartCheck = Sps;
}

bool GameDataManager::GettPlayerStart()
{
	return StartCheck;
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

float GameDataManager::GetBGMVAL()
{
	return BGMVAL*0.1f;
}

void GameDataManager::SetSEVAL(int SE)
{
	SE_VAL = SE;
}

float GameDataManager::GetSEVAL()
{
	return SE_VAL*0.1f;
}

void GameDataManager::SetAIMSPD(int AIM)
{
	AIM_SPD = AIM;
}

int GameDataManager::GetAIMSPD()
{
	return AIM_SPD;
}

void GameDataManager::SetSceneNum(int scene)
{
	SceneNumber = scene;
}

int GameDataManager::GetSceneNum()
{
	return SceneNumber;
}
