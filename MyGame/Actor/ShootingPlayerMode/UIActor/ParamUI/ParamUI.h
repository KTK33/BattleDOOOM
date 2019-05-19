#pragma once
#include "../Math/MathH.h"

class ParamUI
{
public:
	void initialize();

	void SetHP(int hp);

	void SetRemainGun(int bullets);

	void SetHaveGun(int bullets);

	void SetAimPos(Vector3 pos,bool check);

	void SetGunEmpty(bool check);

	void draw()const;

private:
	int mHP;
	int mRemainGun;
	int mHaveGun;
	Vector3 mAimPos;
	bool mAimCheck;
	bool mGunEmpty;
};