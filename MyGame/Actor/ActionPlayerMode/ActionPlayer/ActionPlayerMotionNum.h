#pragma once

//���[�V�����ԍ�
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
		MotionPlayerAvoidance,//���
		MotionPlayerAvoidanceAttack,//����U��
		MotionPlayerDead,
	};
};