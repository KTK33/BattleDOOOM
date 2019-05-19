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

	//�A�N�V�����v���C���[�̃X�e�C�g
	ActionPlayerIdel,
	ActionPlayerWalk,
	ActionPlayerRun,
	ActionPlayerJump,
	ActionPlayerDamage,
	ActionPlayerDead,
	ActionPlayerAvoidance,
	ActionPlayerAttack,
	ActionPlayerAvoidanceAttack,

	//�Ԏ��̃X�e�C�g
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