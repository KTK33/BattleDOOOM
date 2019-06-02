#ifndef ACTOR_GROUP_H_
#define ACTOR_GROUP_H_

//�A�N�^�[�O���[�v
enum class ActorGroup {
	ETCETERA_ACTOR,
	Enemy,        //�G
	BossEnemy,
	EnemyHead,
	PlayerBullet, //�v���C���[�e
	Item,
	EnemyBullet,  //�G�e
	TitleActor,  //�^�C�g����
	Ball,
	Effect,       //�G�t�F�N�g
	Player,       //�v���C���[
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