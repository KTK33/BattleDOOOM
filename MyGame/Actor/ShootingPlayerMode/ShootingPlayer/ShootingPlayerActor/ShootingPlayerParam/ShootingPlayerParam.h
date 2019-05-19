#pragma once
#include "../Math/Vector3.h"

class ShootingPlayerParam {
	ShootingPlayerParam() {}

public:
	static ShootingPlayerParam& getInstance() {
		static ShootingPlayerParam gdm;
		return gdm;
	}

	void initialize();

	//残弾数(セットされている)
	int Get_RemainGun();
	void Set_RemainGun(int bullets);
	void Red_RemainGun(int bullets);


	//持っている弾数
	int Get_HaveGun();
	void Set_HaveGun(int bullets);

	//攻撃力
	int Get_AttackParam();
	void Set_AttackParam(int param);

	//照準のポジション
	Vector3 Get_AimPos();
	void Set_AimPos(Vector3 pos);

	//エイム中か？
	bool Get_AimCheck();
	void Set_AimCheck(bool check);

	bool Get_invincibly();
	void Set_Invicibly(bool check);

private:

	int mRemainGun;
	int mHaveGun;
	int mAttackParam;
	Vector3 mAimPos;
	bool mAimCheck;
	bool mInvCheck;
};
