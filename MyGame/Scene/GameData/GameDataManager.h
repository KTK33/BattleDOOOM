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

	void SetDeadBossEnemy(bool db);
	bool GetDeadBossEnemy();
	void SetPlayerDead(bool pd);
	bool GetPlayerDead();

	void SetRecoverItemCount(int RI);
	int GetRecoverItemCount();

private:

	bool DeadBossEnemyCheck{ false };
	bool DeadPlayerCheck{ false };
	int RecoverItemCount{ 2 };
};
