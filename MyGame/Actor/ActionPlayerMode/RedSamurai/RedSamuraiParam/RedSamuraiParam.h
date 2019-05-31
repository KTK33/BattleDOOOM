#pragma once
#include "../Actor/ActorState/ActorStateID.h"
#include "../Math/Vector3.h"

class RedSamuraiParam {
	RedSamuraiParam() {}

public:
	static RedSamuraiParam& getInstance() {
		static RedSamuraiParam gdm;
		return gdm;
	}

	void initialize();

	//����̈ʒu(��)
	void SetSwardPosNum(int num);
	int GetSwardPosNum();

	//����̃��f���ԍ�(��)
	void SetSwardModelNum(int num);
	int GetSwardModelNum();

	//�A�N�V�������[�h�v���C���[�̃X�e�C�g
	void SetPlayerState(ActorStateID id);
	ActorStateID GetPlayerState();

	//�~�߂�
	void SetRedSamuraiStop(bool s);
	bool GetRedSamuraiStop();

private:
	int mswardnum{ 0 };
	int mswardModelNum{ 0 };
	ActorStateID mstate{ActorStateID::NONE};
	bool mstop{ false };
};
