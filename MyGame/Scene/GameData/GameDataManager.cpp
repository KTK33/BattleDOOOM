#include "GameDataManager.h"

void GameDataManager::initialize()
{
	mTitleCheck = false;
	mStartCheck = false;
	mDeadBossEnemyCheck = false;
	mDeadPlayerCheck = false;
	mSceneNumber = 0;
	mNextAction = false;
}

void GameDataManager::update()
{
}

void GameDataManager::SetTitleCheck(bool Stc)
{
	mTitleCheck = Stc;
}

bool GameDataManager::GetTitleCheck()
{
	return mTitleCheck;
}

void GameDataManager::SetPlayerStart(bool Sps)
{
	mStartCheck = Sps;
}

bool GameDataManager::GettPlayerStart()
{
	return mStartCheck;
}

void GameDataManager::SetDeadBossEnemy(bool db)
{
	mDeadBossEnemyCheck = db;
}

bool GameDataManager::GetDeadBossEnemy()
{
	return mDeadBossEnemyCheck;
}

void GameDataManager::SetPlayerDead(bool pd)
{
	mDeadPlayerCheck = pd;
}

bool GameDataManager::GetPlayerDead()
{
	return mDeadPlayerCheck;
}

void GameDataManager::SetBGMVAL(int BGM)
{
	mBGMVAL = (float)BGM;
}

float GameDataManager::GetBGMVAL()
{
	return mBGMVAL*0.1f;
}

void GameDataManager::SetSEVAL(int SE)
{
	mSE_VAL = (float)SE;
}

float GameDataManager::GetSEVAL()
{
	return mSE_VAL*0.1f;
}

void GameDataManager::SetAIMSPD(int AIM)
{
	mAIM_SPD = AIM;
}

int GameDataManager::GetAIMSPD()
{
	return mAIM_SPD;
}

void GameDataManager::SetSceneNum(int scene)
{
	mSceneNumber = scene;
}

int GameDataManager::GetSceneNum()
{
	return mSceneNumber;
}

void GameDataManager::SetNextActionScene(bool ac)
{
	mNextAction = ac;
}

bool GameDataManager::GetNextActionScene()
{
	return mNextAction;
}
