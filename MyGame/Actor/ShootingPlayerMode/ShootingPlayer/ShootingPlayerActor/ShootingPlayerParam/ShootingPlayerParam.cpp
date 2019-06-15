#include "ShootingPlayerParam.h"
#include "../Game/Define.h"

void ShootingPlayerParam::initialize()
{
	mRemainGun = SetGunPoint;
	mHaveGun = InitHaveGun;
	mAttackParam = 1;
	mAimPos = Vector3::Zero;
	mAimCheck = false;
	mItemBox = false;
	mWeaponNum = 1;
	mGuard = false;
	mItemUse = false;
	mItemType = 0;
}

int ShootingPlayerParam::Get_RemainGun()
{
	return mRemainGun;
}

void ShootingPlayerParam::Set_RemainGun(int bullets)
{
	mRemainGun = bullets;
}

void ShootingPlayerParam::Red_RemainGun(int bullets)
{
	mRemainGun -= bullets;
}

int ShootingPlayerParam::Get_HaveGun()
{
	return mHaveGun;
}

void ShootingPlayerParam::Set_HaveGun(int bullets)
{
	mHaveGun = bullets;
}

int ShootingPlayerParam::Get_AttackParam()
{
	return mAttackParam;
}

void ShootingPlayerParam::Set_AttackParam(int param)
{
	mAttackParam = param;
}

Vector3 ShootingPlayerParam::Get_AimPos()
{
	return mAimPos;
}

void ShootingPlayerParam::Set_AimPos(Vector3 pos)
{
	mAimPos = pos;
}

bool ShootingPlayerParam::Get_AimCheck()
{
	return mAimCheck;
}

void ShootingPlayerParam::Set_AimCheck(bool check)
{
	mAimCheck = check;
}

void ShootingPlayerParam::Set_ItemBoXOpen(bool ibx)
{
	mItemBox = ibx;
}

bool ShootingPlayerParam::Get_ItemBoxOpen()
{
	return mItemBox;
}

void ShootingPlayerParam::Set_WeaponModel(int num)
{
	mWeaponNum = num;
}

int ShootingPlayerParam::Get_WeaponModel()
{
	return mWeaponNum;
}

void ShootingPlayerParam::Set_Guard(bool g)
{
	mGuard = g;
}

bool ShootingPlayerParam::Get_Guard()
{
	return mGuard;
}

void ShootingPlayerParam::Set_ItemUse(bool i, int type)
{
	mItemUse = i;
	mItemType = type;
}

bool ShootingPlayerParam::Get_ItemUse()
{
	return mItemUse;
}

int ShootingPlayerParam::Get_ItemType()
{
	return mItemType;
}
