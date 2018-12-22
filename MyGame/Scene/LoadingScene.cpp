#include "LoadingScene.h"
#include<string>

#include "../Skybox/Skybox.h"
#include "../Mesh/CollisionMesh.h"
#include "../Billboard/Billboard.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"

LoadingScene::LoadingScene() {

	next_ = SceneType::SCENE_GAMEPLAY;
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
}
void LoadingScene::LoadModel() 
{
	//モデルデータの読み込み
	SkeletalMesh::load(0,"asset/MODEL/Model.mv1");
	SkeletalMesh::load(1, "asset/ghoul.mv1");
	StaticMesh::load(0, "asset/w_magun01.mv1");
	SkeletalMesh::load(2, "asset/BaseBall.mv1");

}
void LoadingScene::LoadAny()
{
	CollisionMesh::load(0, "asset/castle/SampleStage_Castle.mv1");
	//スカイボックスモデルの読み込み
	Skybox::load(0, "asset/skybox/skydome.mv1");
	//ビルボードの読み込み
	Billboard::load(0, "asset/Particle02.png");
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


