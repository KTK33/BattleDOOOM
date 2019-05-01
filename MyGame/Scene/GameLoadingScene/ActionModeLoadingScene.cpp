#include "ActionModeLoadingScene.h"
#include "LoadingSceneInc.h"

ActionModeLoadingScene::ActionModeLoadingScene(){

	next_ = SceneType::SCENE_ACTION_PLAY;
}

void ActionModeLoadingScene::start(){

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

void ActionModeLoadingScene::update(float deltaTime){

	if (GetASyncLoadNum() <= 0)
	{
		isEnd_ = true;
	}
}

void ActionModeLoadingScene::draw() const{

	int id[2] = {};
	id[0] = LoadGraph("asset/UI/LoadScene/LoadGauge.png");
	id[1] = LoadGraph("asset/UI/LoadScene/LoadFream.png");
	DrawGraph(210, 800, id[1], FALSE);
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

void ActionModeLoadingScene::end()
{
}

void ActionModeLoadingScene::LoadModel()
{
}

void ActionModeLoadingScene::LoadAny()
{
}

void ActionModeLoadingScene::LoadShader()
{
}

void ActionModeLoadingScene::LoadSound()
{
}

void ActionModeLoadingScene::LoadSprite()
{
}
