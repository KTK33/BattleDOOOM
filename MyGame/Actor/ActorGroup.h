#ifndef ACTOR_GROUP_H_
#define ACTOR_GROUP_H_

//アクターグループ
enum class ActorGroup {
	ETCETERA_ACTOR,
	Player,       //プレイヤー
	Enemy,        //敵
	PlayerBullet, //プレイヤー弾
	EnemyBullet,  //敵弾
	Effect,       //エフェクト
	Ball,         //ボール
	System,
	UI,
};
#endif // !ACTOR_GROUP_H_
