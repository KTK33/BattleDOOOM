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

	//アイテムボックス
	void Set_ItemBoXOpen(bool ibx);
	bool Get_ItemBoxOpen();

	//武器モデル番号
	void Set_WeaponModel(int num);
	int Get_WeaponModel();

	//ガードしているか
	void Set_Guard(bool g);
	bool Get_Guard();

	//アイテムを使ったか
	void Set_ItemUse(bool i,int type);
	bool Get_ItemUse();
	int Get_ItemType();

private:

	int mRemainGun;
	int mHaveGun;
	int mAttackParam;
	Vector3 mAimPos;
	bool mAimCheck;
	bool mItemBox;
	int mWeaponNum;
	bool mGuard;
	bool mItemUse;
	int mItemType;
};
