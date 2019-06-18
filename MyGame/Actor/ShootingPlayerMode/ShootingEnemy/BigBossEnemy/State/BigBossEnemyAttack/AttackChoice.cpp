#include "AttackChoice.h"
#include "../Game/Define.h"
#include "../Math/Random.h"
#include "../Game/GameData/ShootingMode/ShootingBigBossEnemyData.h"

int AttackChoice::AttackType(int BigHP)
{
	float HP3par = BigBossHPVal * 0.3f;
	float HP5par = BigBossHPVal * 0.5f;

	int type = Random::rand(0, 100);

	if (BigHP <= HP3par)//HP‚ª‚RŠ„ˆÈ‰º‚È‚ç
	{
		//UŒ‚‚ÌŠm—¦
		int AttackTypePar[3] = { 20,30,50 };

		return (Attack(type, AttackTypePar[0], AttackTypePar[1]));
	}
	else if(BigHP <= HP5par)//HP‚ª‚TŠ„ˆÈ‰º‚È‚ç
	{
		//UŒ‚‚ÌŠm—¦
		int AttackTypePar[3] = { 30,50,20 };

		return (Attack(type, AttackTypePar[0], AttackTypePar[1]));
	}
	else
	{
		//UŒ‚‚ÌŠm—¦
		int AttackTypePar[3] = { 60,40,0 };

		return (Attack(type, AttackTypePar[0], AttackTypePar[1]));
	}
}

int AttackChoice::Attack(int type, int a1, int a2)
{
	if (type <= a1)
	{
		return 1;
	}
	else if (type <= a1 + a2)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}