#include "ShootingPlayerParam.h"
#include "../Game/Define.h"

void ShootingPlayerParam::initialize()
{
	mRemainGun = SetGunPoint;
	mHaveGun = 10;
	mAttackParam = 1;
	mAimPos = Vector3::Zero;
	mAimCheck = false;
	mItemBox = false;
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