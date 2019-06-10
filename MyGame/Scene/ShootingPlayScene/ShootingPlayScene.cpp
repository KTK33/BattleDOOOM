#include "ShootingPlayScene.h"
#include "../ShootingPlayScene/ShootingModeManager/ShootingModeManager.h"


//コンストラクタ
ShootingPlayScene::ShootingPlayScene() :world_{},
BossArleady{false}
{}

//開始
void ShootingPlayScene::start() {
	world_.initialize();
	GameDataManager::getInstance().initialize();
	Sound::GetInstance().PlayBGM(BGM_ID::PLAY_BGM, DX_PLAYTYPE_LOOP);

	world_.add_actor(ActorGroup::System, new_actor<ShootingModeManager>(&world_));
}

void ShootingPlayScene::update(float deltaTime)
{
	world_.update(deltaTime);


	if (world_.GetBackTitleCheck())
	{
		next_ = SceneType::SCENE_TITLE_LOAD;
		isEnd_ = true;
		return;
	}

}

void ShootingPlayScene::draw() const 
{
	Graphics3D::clear();
	//スカイボックスの描画
	Skybox::bind(0);
	Skybox::draw();
	//ステージの描画
	CollisionMesh::bind(0);
	CollisionMesh::draw();
	
	world_.draw();

	Effekseer_Sync3DSetting();
}
void ShootingPlayScene::end()
{
	Graphics3D::finalize();
	CollisionMesh::finalize();
	Skybox::finalize();
	Sound::GetInstance().Initialize();
	Sprite::GetInstance().Initialize();
}
