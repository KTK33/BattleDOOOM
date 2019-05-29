#include "ActionLoad.h"
#include "../LoadingSceneInc.h"

ActionLoad::ActionLoad()
{
	next_ = SceneType::SCENE_ACTION_PLAY;
}

void ActionLoad::start()
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

void ActionLoad::update(float deltaTime)
{
	if (GetASyncLoadNum() <= 0)
	{
		isEnd_ = true;
	}
}

void ActionLoad::draw() const
{
	//ロード画面の描画
	mDL.draw(2, GetASyncLoadNum());
}

void ActionLoad::end(){}

void ActionLoad::LoadModel()
{
	//ステージモデルの読み込み
	CollisionMesh::load(0, "asset/stage/Stage/arena.mv1");
	//スカイボックスモデルの読み込み
	Skybox::load(0, "asset/skybox/skydome.mv1");

	//モデルデータの読み込み
	SkeletalMesh::load(50, "asset/MODEL/ActionPlayer/ActionPlayer.mv1");
	SkeletalMesh::load(51, "asset/MODEL/RedSamurai/RedSamurai.mv1");
	StaticMesh::load(10, "asset/Weapon/ActionPlayer/dagger.mv1");
	StaticMesh::load(11, "asset/Weapon/Samurai/katana.mv1");
	StaticMesh::load(12, "asset/Weapon/Arrow/Bow.mv1");
	StaticMesh::load(13, "asset/Weapon/Arrow/Quiver.mv1");
	SkeletalMesh::load(52, "asset/Weapon/Arrow/Arrow.mv1");
}

void ActionLoad::LoadSound()
{
	auto& sound = Sound::GetInstance();

	sound.LoadBGM("asset/Sound/BGM/ActionGameBGM.mp3", BGM_ID::ACTION_PLAY_BGM);
	sound.LoadSE("asset/Sound/SE/Arrow.mp3", SE_ID::ARROW);
	sound.LoadSE("asset/Sound/SE/ActionPlayerSward.mp3", SE_ID::ACTION_SWARD);
	sound.LoadSE("asset/Sound/SE/RedSamuraiSward.mp3", SE_ID::RED_SWARD);
	sound.LoadSE("asset/Sound/SE/ActionStep.mp3", SE_ID::ACTION_STEP);
}

void ActionLoad::LoadSprite()
{
	auto& sprite = Sprite::GetInstance();
	//アクションモードのUI
	sprite.Load("asset/UI/ActionModePause/PauseBack.png", SPRITE_ID::ACTIONPAUSE_BACK);
	sprite.Load("asset/UI/ActionModePause/Operation.png", SPRITE_ID::ACTIONPAUSE_OPERATION);
	sprite.Load("asset/UI/ActionModePause/OperationUI.png", SPRITE_ID::ACTIONPAUSE_OPERATION_UI);
	sprite.Load("asset/UI/ActionModePause/TitleBackUI.png", SPRITE_ID::ACTIONPAUSE_TITLEBACK);
	sprite.Load("asset/UI/ActionModePause/cursor.png", SPRITE_ID::ACTIONPAUSE_CURSOR);

	sprite.Load("asset/UI/ActionMode/APlayerHPFrame.png", SPRITE_ID::ACTION_PLAYER_HPFRAME);
	sprite.Load("asset/UI/ActionMode/APlayerHPGauge.png", SPRITE_ID::ACTION_PLAYER_HPGAUGE);
	sprite.Load("asset/UI/ActionMode/RedSamuraiHPFrame.png", SPRITE_ID::REDSAMURAI_HPFRAME);
	sprite.Load("asset/UI/ActionMode/RedSamuraiHPGauge.png", SPRITE_ID::REDSAMURAI_HPGAUGE);

	sprite.Load("asset/UI/ActionMode/ActionPlayerDead.png", SPRITE_ID::ACTIONPLAYERDEAD);
	sprite.Load("asset/UI/ActionMode/RedSamuraiDead.png", SPRITE_ID::REDSAMURAIDEAD);
}
