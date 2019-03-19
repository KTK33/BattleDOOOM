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

	void SetDeadBossEnemy(bool db);
	bool GetDeadBossEnemy();
	void SetPlayerDead(bool pd);
	bool GetPlayerDead();

	void SetItemBoXOpen(bool IBX);
	bool GetItemBoxOpen();

	void SetSightCheck(bool SC);
	bool GetSightCheck();

	void SetBGMVAL(int BGM);
	int GetBGMVAL();
	void SetSEVAL(int SE);
	int GetSEVAL();
	void SetAIMSPD(int AIM);
	int GetAIMSPD();


private:

	bool TitleCheck{ false };
	bool DeadBossEnemyCheck{ false };
	bool DeadPlayerCheck{ false };
	bool ItemBoxOpne{ false };
	bool SightCheck{ false };

	int BGMVAL;
    int SE_VAL;
	int AIM_SPD;
};
