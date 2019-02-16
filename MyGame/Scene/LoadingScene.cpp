#include "LoadingScene.h"
#include<string>

#include "../Texture/Sprite.h"
#include "../Skybox/Skybox.h"
#include "../Mesh/CollisionMesh.h"
#include "../Billboard/Billboard.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"

#include "../Texture/SpriteID.h"

LoadingScene::LoadingScene() {

	next_ = SceneType::SCENE_TITLE;
}

void LoadingScene::start() {
	CollisionMesh::initialize();
	Skybox::initialize();
	Billboard::initialize();

	//各種リソースのロードを行う
	LoadSprite();
	LoadAny();
	LoadModel();
	LoadShader();
	isEnd_ = true;
}

void LoadingScene::update(float deltaTime) {

}

void LoadingScene::draw() const {

}

void LoadingScene::end() {
}

void LoadingScene::LoadSprite()
{
	auto& sprite = Sprite::GetInstance();
	//タイトル画面のUI
	sprite.Load("asset/UI/TitleScene/TitleName.png", SPRITE_ID::TITLENAME);

	//ゲーム画面のUI
	sprite.Load("asset/UI/PlayScene/TextFrame.png",SPRITE_ID::TEXTFRAME);
	sprite.Load("asset/UI/PlayScene/TextBossAppear.png", SPRITE_ID::TEXTBOSSAPPEAR);
	sprite.Load("asset/UI/PlayScene/TextDummyDead.png", SPRITE_ID::TEXTDUMMYDEAD);
	sprite.Load("asset/UI/PlayScene/HP_ui.png", SPRITE_ID::HP_UI);
	sprite.Load("asset/UI/PlayScene/HP_gauge.png", SPRITE_ID::HP_GAUGE);
	sprite.Load("asset/UI/PlayScene/Number.png", SPRITE_ID::NUMBER);
	sprite.Load("asset/UI/PlayScene/Number_thrash.png", SPRITE_ID::THRASH);
	sprite.Load("asset/UI/PlayScene/GunFream.png", SPRITE_ID::GUN_FREAM);
	sprite.Load("asset/UI/PlayScene/HPRecoverText.png", SPRITE_ID::HPRECOVERTEXT);
	sprite.Load("asset/UI/PlayScene/RecoverItemUI.png", SPRITE_ID::HPRECOVERUI);

	//ポーズ画面のUI
	sprite.Load("asset/UI/Pause/PauseBack.png", SPRITE_ID::PAUSEBACK);
}
void LoadingScene::LoadModel()
{
	//モデルデータの読み込み
	SkeletalMesh::load(0,"asset/MODEL/Player/Model.mv1");
	SkeletalMesh::load(1, "asset/MODEL/DummyEnemy/zombie.mv1");
	SkeletalMesh::load(4, "asset/ghoul2.mv1");
	SkeletalMesh::load(2, "asset/BaseBall.mv1");
	SkeletalMesh::load(3, "asset/MODEL/BossMonster/Monster.mv1");
	StaticMesh::load(0, "asset/w_magun01.mv1");

	SkeletalMesh::load(10, "asset/MODEL/ExMonster/motion/parasite_l_starkie.mv1");
}
void LoadingScene::LoadAny()
{
	CollisionMesh::load(0, "asset/castle/SampleStage_Castle.mv1");
	//スカイボックスモデルの読み込み
	Skybox::load(0, "asset/skybox/skydome.mv1");
	//ビルボードの読み込み
	Billboard::load(0, "asset/UI/PlayScene/GunFream.png");
}
void LoadingScene::LoadShader() {
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


