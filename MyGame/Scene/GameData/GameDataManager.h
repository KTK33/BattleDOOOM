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

	//�^�C�g���ɖ߂�
	void SetTitleCheck(bool Stc);
	bool GetTitleCheck();

	void SetPlayerStart(bool Sps);
	bool GettPlayerStart();

	//�{�X������ł��邩�H
	void SetDeadBossEnemy(bool db);
	bool GetDeadBossEnemy();

	//�v���C���[������ł��邩�H
	void SetPlayerDead(bool pd);
	bool GetPlayerDead();

	//BGM�̃{�����[��
	void SetBGMVAL(int BGM);
	float GetBGMVAL();

	//SE�̃{�����[��
	void SetSEVAL(int SE);
	float GetSEVAL();

	//�G�C���̑��x
	void SetAIMSPD(int AIM);
	int GetAIMSPD();

	//�V�[���ԍ�
	void SetSceneNum(int scene);
	int GetSceneNum();

	//���̓A�N�V�����V�[��
	void SetNextActionScene(bool ac);
	bool GetNextActionScene();

private:

	bool mTitleCheck{ false };
	bool mStartCheck{ false };
	bool mDeadBossEnemyCheck{ false };
	bool mDeadPlayerCheck{ false };

	float mBGMVAL{ BGMVOLUME * 10 };
	float mSE_VAL{ SEVOLUME * 10 };
	int mAIM_SPD{ 5 };

	int mSceneNumber{ 2 };

	bool mNextAction{ false };
};