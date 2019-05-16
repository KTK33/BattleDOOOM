#pragma once

enum class ActorStateID
{
	NONE,

	//シューティングプレイヤーのステイト
	ShootingPlayerIdel,
	ShootingPlayerGun,
	ShootingPlayerForwardGun,
	ShootingPlayerRightGun,
	ShootingPlayerLeftGun,
	ShootingPlayerBackGun,
	ShootingPlayerReload,
	ShootingPlayerIdleToAim,
	ShootingPlayerAimToIdle,
	ShootingPlayerDamage,
	ShootingPlayerDamageGun,
	ShootingPlayerDead,
	ShootingPlayerGunPunch,
	ShootingPlayerRun,
	ShootingPlayerIdleAiming,
	ShootingPlayerMove,
	ShootingPlayerThohatu,
	ShootingPlayerJump,

	//アクションプレイヤーのステイト
	ActionPlayerIdel,
	ActionPlayerWalk,
	ActionPlayerRun,
	ActionPlayerJump,
	ActionPlayerDamage,
	ActionPlayerDead,
	ActionPlayerAvoidance,
	ActionPlayerAttack,
	ActionPlayerAvoidanceAttack,

	//赤侍のステイト
	RedSamuraiIdel,
	RedSamuraiWalk,
	RedSamuraiForWard,
	RedSamuraiBackWard,
	RedSamuraiRight,
	RedSamuraiLeft,
	RedSamuraiAttack,
	RedSamuraiAttackArrow,
	RedSamuraiDead,
};