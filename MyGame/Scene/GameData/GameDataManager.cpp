#include "GameDataManager.h"

void GameDataManager::initialize()
{
	DeadBossEnemyCheck = false;
	DeadPlayerCheck = false;
}

void GameDataManager::update()
{
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
