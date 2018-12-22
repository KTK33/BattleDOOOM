#ifndef PLAYER_STATE_H_
#define PLAYER_STATE_H_

class PlayerState
{
public:
	enum  State
	{
		IDLE, //待機      0
		MOVE, //移動      1
		JUMP, //ジャンプ  2
		PUNCH,//パンチ    3 
		KICK, //キック    4
		SWORD,//剣        5
		GUN,  //銃        6   
		DAMAGE,//ダメージ 7
	};
};

#endif // !PLAYER_STATE_H_
