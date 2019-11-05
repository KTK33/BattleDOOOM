#pragma once
#include "../Actor.h"
#include "../Math/Matrix.h"
#include "../Actor/EnemyAttackCollison/EnemyAttackCollison.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/EnemyAttackFire/EnemyAttackFire.h"

//アクターの透明化クラス
class ActorSystem
{
public:

	//透明化
	void TransparenceInit();
	void ActorTransparence();

protected:
	float TargetAngle{ 2.5f };
	float Alpha{ 1.0f };
	bool AlphaCheck{ 0 };

	float gravity{ 9.8f*0.1f };
	bool Stagecollide{ false };
	bool Floorcollide{ false };

	float mpushheight{ 9.8f };

};
