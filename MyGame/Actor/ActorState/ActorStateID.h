#pragma once

enum class ActorStateID
{
	NONE,

	//�V���[�e�B���O�v���C���[�̃X�e�C�g
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

	//�V���[�e�B���O���[�h�̃m�[�}���G�l�~�[�̃X�e�C�g
	NormalEnemyIdle,
	NormalEnemyPunch,
	NormalEnemyRoar,
	NormalEnemyDamage,
	NormalEnemyDead,

	//�V���[�e�B���O���[�h�̃{�X�G�l�~�[�̃X�e�C�g
	BossEnemyIdle,
	BossEnemyPunch,
	BossEnemyFireBefo,
	BossEnemyFire,
	BossEnemyDamage,
	BossEnemyDead,



	//�A�N�V�����v���C���[�̃X�e�C�g
	ActionPlayerIdle,
	ActionPlayerWalk,
	ActionPlayerRun,
	ActionPlayerJump,
	ActionPlayerDamage,
	ActionPlayerDead,
	ActionPlayerAvoidance,
	ActionPlayerAttack,
	ActionPlayerAvoidanceAttack,

	//�Ԏ��̃X�e�C�g
	RedSamuraiIdle,
	RedSamuraiAttack,
	RedSamuraiAttackArrow,
	RedSamuraiDead,
	RedSamuraiPlayerDead,
	RedSamuraiPlayerDeadAfter,
	RedSamuraNoSwardIdle,
};