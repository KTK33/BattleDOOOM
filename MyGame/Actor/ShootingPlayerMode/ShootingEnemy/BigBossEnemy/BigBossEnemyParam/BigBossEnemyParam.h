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

	//�V���[�e�B���O���[�h�v���C���[�̃X�e�C�g
	void SetPlayerState(ActorStateID id);
	ActorStateID GetPlayerState();

	void SetPlayerHP(int hp);
	int GetPlayerHP();

private:
	ActorStateID mstate{ ActorStateID::NONE };
	int mhp;
};
