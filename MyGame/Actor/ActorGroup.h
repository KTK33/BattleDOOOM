#ifndef ACTOR_GROUP_H_
#define ACTOR_GROUP_H_

//アクターグループ
enum class ActorGroup {
	ETCETERA_ACTOR,
	Enemy,        //敵
	BossEnemy,
	BigBossEnemy,
	EnemyHead,
	PlayerBullet, //プレイヤー弾
	Item,
	EnemyBullet,  //敵弾
	TitleActor,  //タイトルの
	Ball,
	Effect,       //エフェクト
	Player,       //プレイヤー
	System,
	UIBefore,
	UI,
	PauseUI,
	ItemBoxUI,
	ItemBoxUIUI,
	GameStartUI,
	GameFinishUI,
	Fade,
};
#endif // !ACTOR_GROUP_H_