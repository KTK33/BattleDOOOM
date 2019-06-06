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

	//�c�e��(�Z�b�g����Ă���)
	int Get_RemainGun();
	void Set_RemainGun(int bullets);
	void Red_RemainGun(int bullets);


	//�����Ă���e��
	int Get_HaveGun();
	void Set_HaveGun(int bullets);

	//�U����
	int Get_AttackParam();
	void Set_AttackParam(int param);

	//�Ə��̃|�W�V����
	Vector3 Get_AimPos();
	void Set_AimPos(Vector3 pos);

	//�G�C�������H
	bool Get_AimCheck();
	void Set_AimCheck(bool check);

	//�A�C�e���{�b�N�X
	void Set_ItemBoXOpen(bool ibx);
	bool Get_ItemBoxOpen();

	//���탂�f���ԍ�
	void Set_WeaponModel(int num);
	int Get_WeaponModel();

	//�K�[�h���Ă��邩
	void Set_Guard(bool g);
	bool Get_Guard();

private:

	int mRemainGun;
	int mHaveGun;
	int mAttackParam;
	Vector3 mAimPos;
	bool mAimCheck;
	bool mItemBox;
	int mWeaponNum;
	bool mGuard;

};
