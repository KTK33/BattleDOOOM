#ifndef ACTOR_GROUP_H_
#define ACTOR_GROUP_H_

//アクターグループ
enum class ActorGroup {
	ETCETERA_ACTOR,
	Enemy,        //敵
	EnemyHead,
	PlayerBullet, //プレイヤー弾
	Item,
	EnemyBullet,  //敵弾
	Ball,         //ボール
	Effect,       //エフェクト
	Player,       //プレイヤー
	System,
	UIBefore,
	UI,
	PauseUI,
	ItemBoxUI,
	ItemBoxUIUI,
	GameOverUI,
	Fade,
};
#endif // !ACTOR_GROUP_H_
