#ifndef PLAYER_STATE_H_
#define PLAYER_STATE_H_

class PlayerState
{
public:
	enum  State
	{
		PlayerIdel,
		PlayerStopGun,
		PlayerForwardGun,
		PlayerRightGun,
		PlayerLeftGun,
		PlayerBackGun,
		PlayerReload,
		PlayerIdleToAim,
		PlayerAimToIdle,
		PlayerDamage,
		PlayerDamageGun,
		PlayerDead,
		PlayerGunPunch,
		PlayerRun,
		PlayerIdleAiming,
		PlayerMove,
		PlayerThohatu,
		PlayerJump,
		NONE,
	};
};

#endif // !PLAYER_STATE_H_
