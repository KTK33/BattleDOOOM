#pragma once

class ActionPlayerState{
public:
	enum State
	{
		NONE,
		ActionPlayerIdel,
		ActionPlayerWalk,
		ActionPlayerRun,
		ActionPlayerJump,
		ActionPlayerDamage,
		ActionPlayerDead,
		ActionPlayerAvoidance,
		ActionPlayerAttack,
		ActionPlayerAvoidanceAttack,
	};
};
