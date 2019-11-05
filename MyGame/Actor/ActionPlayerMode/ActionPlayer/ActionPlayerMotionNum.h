#pragma once

//ƒ‚[ƒVƒ‡ƒ“”Ô†
class ActionPlayerMotion
{
public:
	enum  Motion
	{
		MotionPlayerIdle = 0,
		MotionPlayerWalk,
		MotionPlayerAttack1,
		MotionPlayerAttack2,
		MotionPlayerAttack3,
		MotionPlayerRun,
		MotionPlayerAvoidance,//‰ñ”ğ
		MotionPlayerAvoidanceAttack,//‰ñ”ğUŒ‚
		MotionPlayerDead,
	};
};