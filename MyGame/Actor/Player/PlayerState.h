#ifndef PLAYER_STATE_H_
#define PLAYER_STATE_H_

class PlayerState
{
public:
	enum  State
	{
		IDLE, //�ҋ@      0
		MOVE, //�ړ�      1
		JUMP, //�W�����v  2
		PUNCH,//�p���`    3 
		KICK, //�L�b�N    4
		SWORD,//��        5
		GUN,  //�e        6   
		DAMAGE,//�_���[�W 7
	};
};

#endif // !PLAYER_STATE_H_
