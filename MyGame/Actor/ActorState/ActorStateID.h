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
	ShootingPlayerGuard,
	ShootingPlayerItemUse,

	//シューティングモードのノーマルエネミーのステイト
	NormalEnemyIdle,
	NormalEnemyPunch,
	NormalEnemyRoar,
	NormalEnemyDamage,
	NormalEnemyDead,

	//シューティングモードのボスエネミーのステイト
	BossEnemyIdle,
	BossEnemyPunch,
	BossEnemyFireBefo,
	BossEnemyFire,
	BossEnemyDamage,
	BossEnemyDead,

	//シューティングモードのビッグボスエネミーのステイト
	BigBossEnemyIdle,
	BigBossEnemyAttack,
	BigBossEnemyDead,

	//アクションプレイヤーのステイト
	ActionPlayerIdle,
	ActionPlayerWalk,
	ActionPlayerRun,
	ActionPlayerJump,
	ActionPlayerDamage,
	ActionPlayerDead,
	ActionPlayerAvoidance,
	ActionPlayerAttack,
	ActionPlayerAvoidanceAttack,

	//赤侍のステイト
	RedSamuraiIdle,
	RedSamuraiAttack,
	RedSamuraiAttackArrow,
	RedSamuraiDead,
	RedSamuraiPlayerDead,
	RedSamuraiPlayerDeadAfter,
	RedSamuraNoSwardIdle,
};