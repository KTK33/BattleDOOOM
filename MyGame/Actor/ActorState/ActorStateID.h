#pragma once

enum class ActorStateID
{
	NONE,

	//シューティングプレイヤーのステイト
	ShootingPlayerIdle,
	ShootingPlayerGun,
	ShootingPlayerReload,
	ShootingPlayerIdleToAim,
	ShootingPlayerIdleAiming,
	ShootingPlayerAimToIdle,
	ShootingPlayerDamage,
	ShootingPlayerDead,
	ShootingPlayerGunPunch,
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