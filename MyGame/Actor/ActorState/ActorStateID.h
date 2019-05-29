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
	RedSamuraiAttack,
	RedSamuraiAttackArrow,
	RedSamuraiDead,
	RedSamuraiPlayerDead,
};