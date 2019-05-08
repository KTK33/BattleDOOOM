#include "LoadingScene.h"
#include "LoadingSceneInc.h"

LoadingScene::LoadingScene() {

	next_ = SceneType::SCENE_TITLE;
}

void LoadingScene::start() {

	CollisionMesh::initialize();
	Skybox::initialize();
	Billboard::initialize();
	//非同期開始
	SetUseASyncLoadFlag(TRUE);
	//各種リソースのロードを行う
	LoadAny();
	LoadModel();
	LoadShader();
	LoadSound();
	LoadSprite();
	SetUseASyncLoadFlag(FALSE);
	Countres = GetASyncLoadNum();
}

void LoadingScene::update(float deltaTime) {

	if (GetASyncLoadNum() <= 0) 
	{
		isEnd_ = true;
	}
}

void LoadingScene::draw() const {

	int id[2] = {};
	id[0] = LoadGraph("asset/UI/LoadScene/LoadGauge.png");
	id[1] = LoadGraph("asset/UI/LoadScene/LoadFream.png");
	DrawGraph(210, 800, id[1],FALSE);
	DrawRectGraphF(215, 805, 0, 0, 1490 / Countres * (Countres - GetASyncLoadNum()), 40, id[0], false);
	// 読み込んだ画像のグラフィックハンドルを削除
	if (GetASyncLoadNum() <= 0)
	{
		for (int i = 0; i < 2; i++)
		{
			DeleteGraph(id[i]);
		}
	}

}

void LoadingScene::end() {
}

void LoadingScene::LoadModel()
{
	//モデルデータの読み込み
	SkeletalMesh::load(0,"asset/MODEL/Player/Model.mv1");
	SkeletalMesh::load(11, "asset/MODEL/DummyEnemy/Zombei_1/zombie.mv1");
	SkeletalMesh::load(12, "asset/MODEL/DummyEnemy/Zombei_2/zombie.mv1");
	SkeletalMesh::load(13, "asset/MODEL/DummyEnemy/Zombei_3/zombie.mv1");
	SkeletalMesh::load(3, "asset/MODEL/BossMonster/Monster.mv1");
	SkeletalMesh::load(5, "asset/Weapon/Bullet1.mv1");
	SkeletalMesh::load(6, "asset/MODEL/Item/HPRecover/firstaid.mv1");
	SkeletalMesh::load(7, "asset/MODEL/Item/Bullet/BulletItemEX.mv1");
	SkeletalMesh::load(8, "asset/MODEL/BossMonster/Fire/Meteor.mv1");
	StaticMesh::load(1, "asset/Weapon/Italian/Italian machine guns.mv1");

	SkeletalMesh::load(50, "asset/MODEL/ActionPlayer/ActionPlayer.mv1");
	SkeletalMesh::load(51, "asset/MODEL/RedSamurai/RedSamurai.mv1");
	StaticMesh::load(10, "asset/Weapon/ActionPlayer/dagger.mv1");
	StaticMesh::load(11, "asset/Weapon/Samurai/katana.mv1");
	StaticMesh::load(12, "asset/Weapon/Arrow/Bow.mv1");
	StaticMesh::load(13, "asset/Weapon/Arrow/Quiver.mv1");
	SkeletalMesh::load(52, "asset/Weapon/Arrow/Arrow.mv1");

}
void LoadingScene::LoadAny()
{
	CollisionMesh::load(0, "asset/stage/stage/Textures/stage.mv1");
	CollisionMesh::load(1, "asset/stage/ActionModeStage/arena.mv1");
	//スカイボックスモデルの読み込み
	Skybox::load(0, "asset/skybox/skydome.mv1");
	//ビルボードの読み込み
	Billboard::load(0, "asset/UI/PlayScene/GunFream.png");
}
void LoadingScene::LoadShader() {
}

void LoadingScene::LoadSound()
{
	Sound::GetInstance().LoadBGM("asset/Sound/BGM/TitleSceneBGM.mp3", BGM_ID::TITLE_BGM);
	Sound::GetInstance().LoadBGM("asset/Sound/BGM/PlayeSceneBGM.mp3", BGM_ID::PLAYE_BGM);
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

void LoadingScene::LoadSprite()
{
	auto& sprite = Sprite::GetInstance();
	sprite.Load("asset/UI/Fade/TitleBackBlack.png", SPRITE_ID::FADEBLACK);
	//タイトル画面のUI
	sprite.Load("asset/UI/TitleScene/TitleBack.png", SPRITE_ID::TITLEBACK);
	sprite.Load("asset/UI/TitleScene/TitleName.png", SPRITE_ID::TITLENAME);
	sprite.Load("asset/UI/TitleScene/TitleNameBack.png", SPRITE_ID::TITLENAMEBACK);
	sprite.Load("asset/UI/TitleScene/PressStartUI.png", SPRITE_ID::TITLEPRESS_START);
	sprite.Load("asset/UI/TitleScene/TitleBackWhite.png", SPRITE_ID::TITLEBACKWHITE);
	sprite.Load("asset/UI/TitleScene/Choui.png", SPRITE_ID::TITLECHUI);
	sprite.Load("asset/UI/TitleScene/Jikyo.png", SPRITE_ID::TITLEJIKYO);

	//セレクト画面のUI
	sprite.Load("asset/UI/TitleScene/SelectModeBack.png", SPRITE_ID::SELECTBACK);
	sprite.Load("asset/UI/TitleScene/SelectShooting.png", SPRITE_ID::SELECT_SHOOTING);
	sprite.Load("asset/UI/TitleScene/SelectShooting_dec.png", SPRITE_ID::SELECT_SHOOTING_DEC);
	sprite.Load("asset/UI/TitleScene/SelectShootingex.png", SPRITE_ID::SELECT_SHOOTING_EX);
	sprite.Load("asset/UI/TitleScene/SelectAction.png", SPRITE_ID::SELECT_ACTION);
	sprite.Load("asset/UI/TitleScene/SelectAction_dec.png", SPRITE_ID::SELECT_ACTION_DEC);
	sprite.Load("asset/UI/TitleScene/SelectActionex.png", SPRITE_ID::SELECT_ACTION_EX);
	sprite.Load("asset/UI/TitleScene/SelectTitle.png", SPRITE_ID::SELECT_NAME);



	//ゲーム画面のUI
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

	sprite.Load("asset/UI/PlayScene/Enemy/BossHP_.png", SPRITE_ID::BOSSHP_UI);
	sprite.Load("asset/UI/PlayScene/Enemy/BossHP_gauge.png", SPRITE_ID::BOSSHP_GAUGE);
	sprite.Load("asset/UI/PlayScene/Enemy/EnemyCountATO.png", SPRITE_ID::ENEMY_COUNT_ATO);
	sprite.Load("asset/UI/PlayScene/Sight.png", SPRITE_ID::SIGHT);

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
	sprite.Load("asset/UI/Pause/CircleAnime.png", SPRITE_ID::PAUSECIRCLE);

	//エフェクト
	sprite.Load("asset/UI/Effect/BulletHit.png", SPRITE_ID::EFFECT_BULLETHIT);


	//アクションモードのUI

	sprite.Load("asset/UI/ActionModePause/PauseBack.png", SPRITE_ID::ACTIONPAUSE_BACK);
	sprite.Load("asset/UI/ActionModePause/Operation.png", SPRITE_ID::ACTIONPAUSE_OPERATION);
	sprite.Load("asset/UI/ActionModePause/OperationUI.png", SPRITE_ID::ACTIONPAUSE_OPERATION_UI);
	sprite.Load("asset/UI/ActionModePause/TitleBackUI.png", SPRITE_ID::ACTIONPAUSE_TITLEBACK);
	sprite.Load("asset/UI/ActionModePause/cursor.png", SPRITE_ID::ACTIONPAUSE_CURSOR);

}

void LoadingScene::DeleteRes()
{
	Skybox::finalize();
	//モデルデータの削除
	SkeletalMesh::erase(0);
	SkeletalMesh::erase(1);
	StaticMesh::erase(0);
	CollisionMesh::finalize();
	Skybox::finalize();
}


