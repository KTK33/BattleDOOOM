#pragma once
#include "../Math/MathH.h"

class SightUI
{
public:
	void initialize();

	void SetAimPos(Vector3 pos, bool check);

	void draw()const;

private:
	Vector3 mAimPos;
	bool mAimCheck;
};