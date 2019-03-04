#ifndef ACTOR_GROUP_H_
#define ACTOR_GROUP_H_

//アクターグループ
enum class ActorGroup {
	ETCETERA_ACTOR,
	Player,       //プレイヤー
	Enemy,        //敵
	PlayerBullet, //プレイヤー弾
	Item,
	EnemyBullet,  //敵弾
	Effect,       //エフェクト
	Ball,         //ボール
	System,
	UI,
	PauseUI,
	ItemBoxUI,
	ItemBoxUIUI,
};
#endif // !ACTOR_GROUP_H_
