#pragma once
#include "../Game/Define.h"

class GameDataManager {
	GameDataManager() {}

public:
	static GameDataManager& getInstance() {
		static GameDataManager gdm;
		return gdm;
	}

	void initialize();

	void update();

	//タイトルに戻る
	void SetTitleCheck(bool Stc);
	bool GetTitleCheck();

	void SetPlayerStart(bool Sps);
	bool GettPlayerStart();

	//ボスが死んでいるか？
	void SetDeadBossEnemy(bool db);
	bool GetDeadBossEnemy();

	//プレイヤーが死んでいるか？
	void SetPlayerDead(bool pd);
	bool GetPlayerDead();

	//BGMのボリューム
	void SetBGMVAL(int BGM);
	float GetBGMVAL();

	//SEのボリューム
	void SetSEVAL(int SE);
	float GetSEVAL();

	//エイムの速度
	void SetAIMSPD(int AIM);
	int GetAIMSPD();

	//シーン番号
	void SetSceneNum(int scene);
	int GetSceneNum();

	//次はアクションシーン
	void SetNextActionScene(bool ac);
	bool GetNextActionScene();

private:

	bool mTitleCheck{ false };
	bool mStartCheck{ false };
	bool mDeadBossEnemyCheck{ false };
	bool mDeadPlayerCheck{ false };

	float mBGMVAL{ BGMVOLUME * 10 };
	float mSE_VAL{ SEVOLUME * 10 };
	int mAIM_SPD{ 2 };

	int mSceneNumber{ 2 };

	bool mNextAction{ false };
};