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

	void SetTitleCheck(bool Stc);
	bool GetTitleCheck();

	void SetPlayerStart(bool Sps);
	bool GettPlayerStart();

	void SetDeadBossEnemy(bool db);
	bool GetDeadBossEnemy();
	void SetPlayerDead(bool pd);
	bool GetPlayerDead();

	void SetItemBoXOpen(bool IBX);
	bool GetItemBoxOpen();

	void SetSightCheck(bool SC);
	bool GetSightCheck();

	void SetBGMVAL(int BGM);
	float GetBGMVAL();
	void SetSEVAL(int SE);
	float GetSEVAL();
	void SetAIMSPD(int AIM);
	int GetAIMSPD();

	void SetSceneNum(int scene);
	int GetSceneNum();


private:

	bool TitleCheck{ false };
	bool StartCheck{ false };
	bool DeadBossEnemyCheck{ false };
	bool DeadPlayerCheck{ false };
	bool ItemBoxOpne{ false };
	bool SightCheck{ false };

	int BGMVAL{ 5 };
	int SE_VAL{ 7 };
	int AIM_SPD{ 5 };

	int SceneNumber{ 2 };
};
