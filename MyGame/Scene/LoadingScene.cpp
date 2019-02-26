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
	sprite.Load("asset/UI/PlayScene/BulletGetText.png", SPRITE_ID::BULLETGETUI);
	sprite.Load("asset/UI/PlayScene/MissionExtermination.png", SPRITE_ID::MISSION_ENEMY_EXTERMINATION);
	sprite.Load("asset/UI/PlayScene/MissionNumber.png", SPRITE_ID::MISSION_NUMBER);
	sprite.Load("asset/UI/PlayScene/MissionBossDefeat.png", SPRITE_ID::MISSION_BOSS_DEFEAT);

	sprite.Load("asset/UI/PlayScene/Enemy/BossHP_.png", SPRITE_ID::BOSSHP_UI);
	sprite.Load("asset/UI/PlayScene/Enemy/BossHP_gauge.png", SPRITE_ID::BOSSHP_GAUGE);
	sprite.Load("asset/UI/PlayScene/Enemy/EnemyCountATO.png", SPRITE_ID::ENEMY_COUNT_ATO);
	sprite.Load("asset/UI/PlayScene/Sight.png", SPRITE_ID::SIGHT);

	//ポーズ画面のUI
	sprite.Load("asset/UI/Pause/PauseBack.png", SPRITE_ID::PAUSEBACK);
	sprite.Load("asset/UI/Pause/Item.png", SPRITE_ID::ITEM);
	sprite.Load("asset/UI/Pause/ItemUI.png", SPRITE_ID::PAUSEITEM);
	sprite.Load("asset/UI/Pause/Item_description.png", SPRITE_ID::PAUSEITEM_DESCRIPTION);
	sprite.Load("asset/UI/Pause/Operation.png", SPRITE_ID::OPERATION);
	sprite.Load("asset/UI/Pause/OperationUI.png", SPRITE_ID::PAUSEOPERATION);
	sprite.Load("asset/UI/Pause/Operation_description.png", SPRITE_ID::PAUSEOPERATION_DESCRIPTION);
	sprite.Load("asset/UI/Pause/System.png", SPRITE_ID::SYSTEM);
	sprite.Load("asset/UI/Pause/SystemUI.png", SPRITE_ID::PAUSESYSTEM);
	sprite.Load("asset/UI/Pause/System_description.png", SPRITE_ID::PAUSESYSTEM_DESCRIPTION);
	sprite.Load("asset/UI/Pause/TitleUI.png", SPRITE_ID::PAUSETITLE);
	sprite.Load("asset/UI/Pause/Title_description.png", SPRITE_ID::PAUSETITLE_DESCRIPTION);
	sprite.Load("asset/UI/Pause/CircleAnime.png", SPRITE_ID::PAUSECIRCLE);


}
void LoadingScene::LoadModel()
{
	//モデルデータの読み込み
	SkeletalMesh::load(0,"asset/MODEL/Player/Model.mv1");
	SkeletalMesh::load(1, "asset/MODEL/DummyEnemy/zombie.mv1");
	SkeletalMesh::load(4, "asset/ghoul2.mv1");
	SkeletalMesh::load(2, "asset/BaseBall.mv1");
	SkeletalMesh::load(3, "asset/MODEL/BossMonster/Monster.mv1");
	SkeletalMesh::load(5, "asset/Weapon/Bullet.mv1");
	SkeletalMesh::load(6, "asset/MODEL/Item/HPRecover/Wine_Bottle_Red.mv1");
	SkeletalMesh::load(7, "asset/MODEL/Item/Bullet/BulletItemEX.mv1");
	StaticMesh::load(0, "asset/w_magun01.mv1");
	StaticMesh::load(1, "asset/Weapon/Italian/Italian machine guns.mv1");

	SkeletalMesh::load(10, "asset/MODEL/ExMonster/motion/parasite_l_starkie.mv1");
}
void LoadingScene::LoadAny()
{
	//CollisionMesh::load(0, "asset/castle/SampleStage_Castle.mv1");
	CollisionMesh::load(0, "asset/stage/stage/Textures/Stage.mv1");
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


