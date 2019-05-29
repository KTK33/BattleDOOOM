#pragma once

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

	void SetSceneNum(int scene);
	int GetSceneNum();


private:

	bool mTitleCheck{ false };
	bool mStartCheck{ false };
	bool mDeadBossEnemyCheck{ false };
	bool mDeadPlayerCheck{ false };

	int mBGMVAL{ 5 };
	int mSE_VAL{ 7 };
	int mAIM_SPD{ 5 };

	int mSceneNumber{ 2 };
};