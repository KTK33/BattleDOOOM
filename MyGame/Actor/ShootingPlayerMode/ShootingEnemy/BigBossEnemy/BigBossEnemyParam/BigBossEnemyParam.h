#pragma once
#include "../Actor/ActorState/ActorStateID.h"

class BigBossEnemyParam {
	BigBossEnemyParam() {}

public:
	static BigBossEnemyParam& getInstance() {
		static BigBossEnemyParam gdm;
		return gdm;
	}

	void initialize();

	//シューティングモードプレイヤーのステイト
	void SetPlayerState(ActorStateID id);
	ActorStateID GetPlayerState();

	void SetPlayerHP(int hp);
	int GetPlayerHP();

private:
	ActorStateID mstate{ ActorStateID::NONE };
	int mhp;
};
