#pragma once
#include "../Math/MathH.h"

//アクションモードのプレイヤーのHPのクラス
class ActionPlayerHP
{
public:
	void draw(int hp)const;

private:
	int mHP;
};