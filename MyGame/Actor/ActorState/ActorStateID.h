#pragma once

enum class ActorStateID
{
	NONE,

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