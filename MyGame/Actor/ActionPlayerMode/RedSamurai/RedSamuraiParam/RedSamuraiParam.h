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

	//武器の位置(刀)
	void SetSwardPosNum(int num);
	int GetSwardPosNum();

	//武器のモデル番号(刀)
	void SetSwardModelNum(int num);
	int GetSwardModelNum();

	//アクションモードプレイヤーのステイト
	void SetPlayerState(ActorStateID id);
	ActorStateID GetPlayerState();

	//止める
	void SetRedSamuraiStop(bool s);
	bool GetRedSamuraiStop();

private:
	int mswardnum{ 0 };
	int mswardModelNum{ 0 };
	ActorStateID mstate{ActorStateID::NONE};
	bool mstop{ false };
};
