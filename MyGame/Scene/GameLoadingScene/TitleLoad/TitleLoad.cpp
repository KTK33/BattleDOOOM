#include "TitleLoad.h"
#include "../LoadingSceneInc.h"

TitleLoad::TitleLoad()
{
	next_ = SceneType::SCENE_TITLE;
}

void TitleLoad::start()
{
	Sprite::GetInstance().DeleteAll();
	Billboard::initialize();
	Sound::GetInstance().DeleteAll();
	SkeletalMesh::initialize();
	StaticMesh::initialize();
	CollisionMesh::initialize();
	Skybox::initialize();
	EffekseerEffect::initialize();
	//非同期開始
	SetUseASyncLoadFlag(TRUE);
	//タイトルで使用するリソースのロードを行う
	LoadModel();
	LoadSound();
	LoadSprite();
	SetUseASyncLoadFlag(FALSE);

	//ロードするリソース数の設定
	mDL.setCount(GetASyncLoadNum());

	LoadEffect();
}

void TitleLoad::update(float deltaTime)
{
	if (GetASyncLoadNum() <= 0)
	{
		isEnd_ = true;
	}
}

void TitleLoad::draw() const
{
	//ロード画面の描画
	mDL.draw(0, GetASyncLoadNum());
}

void TitleLoad::end(){}

void TitleLoad::LoadModel()
{
	//モデルデータの読み込み
	SkeletalMesh::load(0, "asset/MODEL/Player/Model.mv1");
	SkeletalMesh::load(5, "asset/Weapon/Bullet1.mv1");
	StaticMesh::load(1, "asset/Weapon/Italian/Italian machine guns.mv1");
	StaticMesh::load(2, "asset/Weapon/Italian/Italian machine guns2.mv1");
	SkeletalMesh::load(50, "asset/MODEL/ActionPlayer/ActionPlayer.mv1");
	StaticMesh::load(10, "asset/Weapon/ActionPlayer/dagger.mv1");
}

void TitleLoad::LoadSound()
{
	auto& sound = Sound::GetInstance();
	sound.LoadBGM("asset/Sound/BGM/TitleSceneBGM.mp3", BGM_ID::TITLE_BGM);
	sound.LoadSE("asset/Sound/SE/DamageEnemySE.mp3", SE_ID::DAMAGEENEMY_SE);
	sound.LoadSE("asset/Sound/SE/TitleKetteiSE.mp3", SE_ID::TITLEKETTEI_SE);
	sound.LoadSE("asset/Sound/SE/PauseCursorSE.mp3", SE_ID::PAUSECURSOR_SE);
	sound.LoadSE("asset/Sound/SE/PauseKetteiSE.mp3", SE_ID::PAUSEKETTEI_SE);
	sound.LoadSE("asset/Sound/SE/kaminari.mp3", SE_ID::THUNDER_SE);
}

void TitleLoad::LoadSprite()
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
	sprite.Load("asset/UI/TitleScene/SelectPurposeS.png", SPRITE_ID::SELECT_PUR_S);
	sprite.Load("asset/UI/TitleScene/SelectPurposeA.png", SPRITE_ID::SELECT_PUR_A);

	//エフェクト
	sprite.Load("asset/UI/Effect/BulletHit.png", SPRITE_ID::EFFECT_BULLETHIT);

	//クレジット
	sprite.Load("asset/UI/TitleScene/CreditScene.png", SPRITE_ID::CREDIT);
	sprite.Load("asset/UI/TitleScene/CreditOpenUI.png", SPRITE_ID::CREDIT_OPENBUTTON);
}

void TitleLoad::LoadEffect()
{
	EffekseerEffect::load((int)EFFECT_ID::TITLE_THUNDER, "asset/Effekseer/TitleThunder.efk");
}
