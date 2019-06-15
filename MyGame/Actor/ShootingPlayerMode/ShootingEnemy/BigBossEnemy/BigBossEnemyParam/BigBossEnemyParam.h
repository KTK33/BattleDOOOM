#pragma once

class BigBossEnemyParam {
	BigBossEnemyParam() {}

public:
	static BigBossEnemyParam& getInstance() {
		static BigBossEnemyParam gdm;
		return gdm;
	}

	void initialize();

	void Set_RotaCheck(bool r);
	bool Get_RotaCheck();

private:
	bool mrota;
};
