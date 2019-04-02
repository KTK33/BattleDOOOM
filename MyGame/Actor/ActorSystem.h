#pragma once
#include "Actor.h"
#include "../Math/Matrix.h"
#include "Enemy/EnemyAttack.h"
#include "Enemy/EnemyAttackFire.h"

class ActorSystem
{
public:
	float PlayerDirection(Actor* player, Vector3& position, Matrix& matrix);

	void TransparenceInit();
	void ActorTransparence();

protected:
	float TargetAngle{ 2.5f };
	float Alpha{ 1.0f };
	bool AlphaCheck{ 0 };

	float gravity{ 9.8f*0.1f };
	bool Stagecollide{ false };
	bool Floorcollide{ false };

};
