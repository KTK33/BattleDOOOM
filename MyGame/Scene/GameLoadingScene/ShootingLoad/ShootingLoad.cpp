#include "ShootingLoad.h"
#include "../LoadingSceneInc.h"

ShootingLoad::ShootingLoad()
{
	next_ = SceneType::SCENE_SHOOTING_PLAY;
}

void ShootingLoad::start()
{
	//非同期開始
	SetUseASyncLoadFlag(TRUE);
	//タイトルで使用するリソースのロードを行う
	LoadModel();
	LoadSound();
	LoadSprite();
	SetUseASyncLoadFlag(FALSE);

	//ロードするリソース数の設定
	mDL.setCount(GetASyncLoadNum());
}

void ShootingLoad::update(float deltaTime)
{
	if (GetASyncLoadNum() <= 0)
	{
		isEnd_ = true;
	}
}

void ShootingLoad::draw() const
{
	//ロード画面の描画
	mDL.draw(1, GetASyncLoadNum());
}

void ShootingLoad::end(){}

void ShootingLoad::LoadModel()
{
	//ステージモデルの読み込み
	CollisionMesh::load(0, "asset/stage/Stage/arena.mv1");
	//スカイボックスモデルの読み込み
	Skybox::load(0, "asset/skybox/ShootingMode/sky.mv1");

	//モデルデータの読み込み
	SkeletalMesh::load(11, "asset/MODEL/DummyEnemy/Zombei_1/zombie.mv1");
	SkeletalMesh::load(12, "asset/MODEL/DummyEnemy/Zombei_2/zombie.mv1");
	SkeletalMesh::load(13, "asset/MODEL/DummyEnemy/Zombei_3/zombie.mv1");
	SkeletalMesh::load(3, "asset/MODEL/BossMonster/Monster.mv1");
	SkeletalMesh::load(6, "asset/MODEL/Item/HPRecover/firstaid.mv1");
	SkeletalMesh::load(7, "asset/MODEL/Item/Bullet/BulletItemEX.mv1");
	SkeletalMesh::load(8, "asset/MODEL/BossMonster/Fire/Meteor.mv1");
	SkeletalMesh::load(9, "asset/MODEL/BigBoss/bos.mv1");
}

void ShootingLoad::LoadSound()
{
	Sound::GetInstance().LoadBGM("asset/Sound/BGM/PlayeSceneBGM.mp3", BGM_ID::PLAY_BGM);
	Sound::GetInstance().LoadBGM("asset/Sound/BGM/GameClearBGM.mp3", BGM_ID::WIN_BGM);
	Sound::GetInstance().LoadBGM("asset/Sound/BGM/GameOverBGM.mp3", BGM_ID::LOSE_BGM);

	Sound::GetInstance().LoadSE("asset/Sound/SE/AttackSE.mp3", SE_ID::ATTACK_SE);
	Sound::GetInstance().LoadSE("asset/Sound/SE/DamageEnemySE.mp3", SE_ID::DAMAGEENEMY_SE);
	Sound::GetInstance().LoadSE("asset/Sound/SE/EnemyroarSE.mp3", SE_ID::ENEMYDOAR_SE);
	Sound::GetInstance().LoadSE("asset/Sound/SE/ItemUseSE.mp3", SE_ID::ITEMUSE_SE);
	Sound::GetInstance().LoadSE("asset/Sound/SE/PauseCursorSE.mp3", SE_ID::PAUSECURSOR_SE);
	Sound::GetInstance().LoadSE("asset/Sound/SE/PauseKetteiSE.mp3", SE_ID::PAUSEKETTEI_SE);
	Sound::GetInstance().LoadSE("asset/Sound/SE/ShootSE.mp3", SE_ID::SHOOT_SE);
	Sound::GetInstance().LoadSE("asset/Sound/SE/TitleKetteiSE.mp3", SE_ID::TITLEKETTEI_SE);
	Sound::GetInstance().LoadSE("asset/Sound/SE/Walkstep.mp3", SE_ID::WALKSTEP_SE);
	Sound::GetInstance().LoadSE("asset/Sound/SE/Tyouhatu.mp3", SE_ID::TYOHATU_SE);
	Sound::GetInstance().LoadSE("asset/Sound/SE/ItemGet.mp3", SE_ID::ITEMGET_SE);
}

void ShootingLoad::LoadSprite()
{
	auto& sprite = Sprite::GetInstance();
	//シューティングゲーム画面のUI
	sprite.Load("asset/UI/PlayScene/TextFrame.png", SPRITE_ID::TEXTFRAME);
	sprite.Load("asset/UI/PlayScene/TextBossAppear.png", SPRITE_ID::TEXTBOSSAPPEAR);
	sprite.Load("asset/UI/PlayScene/TextDummyDead.png", SPRITE_ID::TEXTDUMMYDEAD);
	sprite.Load("asset/UI/PlayScene/HP_ui.png", SPRITE_ID::HP_UI);
	sprite.Load("asset/UI/PlayScene/HP_gauge.png", SPRITE_ID::HP_GAUGE);
	sprite.Load("asset/UI/PlayScene/Number.png", SPRITE_ID::NUMBER);
	sprite.Load("asset/UI/PlayScene/Number_thrash.png", SPRITE_ID::THRASH);
	sprite.Load("asset/UI/PlayScene/GunFream.png", SPRITE_ID::GUN_FREAM);
	sprite.Load("asset/UI/PlayScene/HPRecoverText.png", SPRITE_ID::HPRECOVERTEXT);
	sprite.Load("asset/UI/PlayScene/RecoverItemUI.png", SPRITE_ID::HPRECOVERUI);
	sprite.Load("asset/UI/PlayScene/BulletGetText.png", SPRITE_ID::BULLETGETUI);
	sprite.Load("asset/UI/PlayScene/MissionExtermination.png", SPRITE_ID::MISSION_ENEMY_EXTERMINATION);
	sprite.Load("asset/UI/PlayScene/MissionNumber.png", SPRITE_ID::MISSION_NUMBER);
	sprite.Load("asset/UI/PlayScene/MissionBossDefeat.png", SPRITE_ID::MISSION_BOSS_DEFEAT);

	sprite.Load("asset/UI/PlayScene/Enemy/EnemyCountATO.png", SPRITE_ID::ENEMY_COUNT_ATO);
	sprite.Load("asset/UI/PlayScene/Sight.png", SPRITE_ID::SIGHT);

	Billboard::load((int)SPRITE_ID::BOSSHP_UI, "asset/UI/PlayScene/Enemy/BossHP_.png");
	Billboard::load((int)SPRITE_ID::BOSSHP_GAUGE, "asset/UI/PlayScene/Enemy/BossHP_gauge.png");

	sprite.Load("asset/UI/PlayScene/ItemBox.png", SPRITE_ID::ITEMBOX);

	sprite.Load("asset/UI/PlayScene/GameOverBack.png", SPRITE_ID::GAMEOVERBACK);
	sprite.Load("asset/UI/PlayScene/GameOverName.png", SPRITE_ID::GAMEOVERNAME);

	sprite.Load("asset/UI/PlayScene/GameClearBack.png", SPRITE_ID::GAMECLEARBACK);
	sprite.Load("asset/UI/PlayScene/GameClearName.png", SPRITE_ID::GAMECLEARNAME);
	sprite.Load("asset/UI/PlayScene/BulletEmpty.png", SPRITE_ID::BULLET_EMPTY);
	sprite.Load("asset/UI/PlayScene/AttackUp.png", SPRITE_ID::ATTACK_UPNOW);

	//ポーズ画面のUI
	sprite.Load("asset/UI/Pause/PauseBack.png", SPRITE_ID::PAUSEBACK);
	sprite.Load("asset/UI/Pause/Item.png", SPRITE_ID::ITEM);
	sprite.Load("asset/UI/Pause/ItemUI.png", SPRITE_ID::PAUSEITEM);
	sprite.Load("asset/UI/Pause/Item_description.png", SPRITE_ID::PAUSEITEM_DESCRIPTION);
	sprite.Load("asset/UI/Pause/Item_tukau.png", SPRITE_ID::PAUSEITEM_TUKAU);
	sprite.Load("asset/UI/Pause/Item_tukauBack.png", SPRITE_ID::PAUSEITEM_TUKAUBACK);
	sprite.Load("asset/UI/Pause/Operation.png", SPRITE_ID::OPERATION);
	sprite.Load("asset/UI/Pause/OperationUI.png", SPRITE_ID::PAUSEOPERATION);
	sprite.Load("asset/UI/Pause/Operation_description.png", SPRITE_ID::PAUSEOPERATION_DESCRIPTION);
	sprite.Load("asset/UI/Pause/System.png", SPRITE_ID::SYSTEM);
	sprite.Load("asset/UI/Pause/SystemUI.png", SPRITE_ID::PAUSESYSTEM);
	sprite.Load("asset/UI/Pause/System_description.png", SPRITE_ID::PAUSESYSTEM_DESCRIPTION);
	sprite.Load("asset/UI/Pause/System_Fream.png", SPRITE_ID::PAUSESYSTEM_FREAM);
	sprite.Load("asset/UI/Pause/System_FreamS.png", SPRITE_ID::PAUSESYSTEM_FREAMS);
	sprite.Load("asset/UI/Pause/SystemCursor.png", SPRITE_ID::PAUSESYSTEM_CURSOR);

	sprite.Load("asset/UI/Pause/TitleUI.png", SPRITE_ID::PAUSETITLE);
	sprite.Load("asset/UI/Pause/Title_description.png", SPRITE_ID::PAUSETITLE_DESCRIPTION);

	//エフェクト
	sprite.Load("asset/UI/Effect/BulletHit.png", SPRITE_ID::EFFECT_BULLETHIT);
}
