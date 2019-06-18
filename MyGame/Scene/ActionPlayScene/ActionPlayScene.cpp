#include "ActionPlayScene.h"
#include "../ActionPlayScene/ActionModeManager/ActionModeManager.h"
#include "../Game/Define.h"
ActionPlayScene::ActionPlayScene(){}

void ActionPlayScene::start()
{
	world_.initialize();
	GameDataManager::getInstance().initialize();
	Sound::GetInstance().SetAllBGMVolume(BGMVOLUME);
	Sound::GetInstance().SetAllSEVolume(SEVOLUME);
	Sound::GetInstance().PlayBGM(BGM_ID::ACTION_PLAY_BGM, DX_PLAYTYPE_LOOP);

	world_.add_actor(ActorGroup::System, new_actor<ActionModeManager>(&world_));

	Sound::GetInstance().SetAllBGMVolume(0.25f);
}

void ActionPlayScene::update(float deltaTime)
{
	world_.update(deltaTime);

	if (world_.GetBackTitleCheck() == true) {
		next_ = SceneType::SCENE_TITLE_LOAD;
		isEnd_ = true;
	}

	if (GameDataManager::getInstance().GetNextActionScene()== true) {
		next_ = SceneType::SCENE_ACTION_PLAY;
		isEnd_ = true;
	}
}

void ActionPlayScene::draw() const
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

void ActionPlayScene::end()
{}
