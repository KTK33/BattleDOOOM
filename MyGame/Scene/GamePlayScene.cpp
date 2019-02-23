#include "GamePlayScene.h"
//#include "../Actor/Enemy/Enemy.h"
#include "../Actor/PlayerBall/Ball.h"
#include "../Actor/Player/Player.h"
#include "../Actor/Player/PlayerItemBox.h"
#include "../Actor/Enemy/DummyEnemy.h"
#include "../Actor/Enemy/BossEnemy.h"
#include "../Actor/Camera/Camera.h"
#include "../Actor/ActorGroup.h"
#include "../Fiield/Field.h"
#include "../Skybox/Skybox.h"
#include "../Mesh/CollisionMesh.h"
#include "../Billboard/Billboard.h"
#include "../Graphics/Graphics3D.h"
#include "../Fiield/WorldContentManager/WorldContentManager.h"
#include "GameData/GameDataManager.h"
#include "../Input/GamePad.h"
#include "../Actor/UIActor/EnemyDeadText.h"
#include "../Texture/Sprite.h"
#include "../Game/Define.h"
#include "../Actor/UIActor/AnyUI.h"
#include "../Actor/UIActor/PlayerTextUI.h"
#include "../Actor/UIActor/Pause.h"

#include "../Actor/Enemy/ExEnemy.h"

#include<DxLib.h>

//コンストラクタ
GamePlayScene::GamePlayScene() :world_{}
{

}



//開始
void GamePlayScene::start() {
	world_.initialize();
	GameDataManager::getInstance().initialize();

	menuSize_ = 4;
	BossArleady = false;

	//auto P_Box = new_actor<PlayerItemBox>(&world_);
	//world_.add_actor(ActorGroup::Player, P_Box);

	auto P_Text = new_actor<PlayerTextUI>(&world_);
	world_.add_actor(ActorGroup::UI, P_Text);

	auto P = new_actor<Player>(0, 0, &world_, Vector3{ 0.0f, -40.0f,0.0f }, P_Text);
	world_.add_actor(ActorGroup::Player, P);

	world_.add_actor(ActorGroup::UI, new_actor<AnyUI>(&world_,P));

	world_.add_actor(ActorGroup::PauseUI, new_actor<PauseUI>(&world_));

	//world_.add_actor(ActorGroup::Enemy, new_actor<Enemy>(4, &world_, Vector3{ 10.0f, 0.0f,0.0f }));

	for (int i = 0; i < 5; i++)
	{
		auto dummy = new_actor<DummyEnemy>(1, &world_, Vector3{ Random::rand(-70.0f,70.0f), 0.0f,Random::rand(-70.0f,70.0f) }, Matrix::CreateRotationY(Random::rand(0.0f,360.0f)));
		world_.add_actor(ActorGroup::Enemy,dummy);
	}

	//world_.add_actor(ActorGroup::Enemy, new_actor<BossEnemy>(3, &world_, Vector3{ 10.0f, 0.0f,0.0f }));

	//world_.add_actor(ActorGroup::Enemy, new_actor<ExEnemy>(10, &world_, Vector3{ 20.0f, 0.0f,0.0f }));

	world_.add_actor(ActorGroup::System, new_actor<Camera>(&world_));

	world_.add_actor(ActorGroup::UI, new_actor<EnemyDeadText>(&world_));
}

void GamePlayScene::update(float deltaTime)
{
	world_.update(deltaTime);
	//GameDataManager::getInstance().update();

	if (world_.find_actor(ActorGroup::Enemy, "DummyEnemy") == NULL && BossArleady == false)
	{
		world_.add_actor(ActorGroup::Enemy, new_actor<BossEnemy>(3, &world_, Vector3{ 10.0f, 0.0f,0.0f }));
		BossArleady = true;
	}


	if (GameDataManager::getInstance().GetPlayerDead() == true)
	{
		next_ = SceneType::SCENE_GAMEOVER;
		isEnd_ = true;
	}

	if (GameDataManager::getInstance().GetDeadBossEnemy() == true) {
		next_ = SceneType::SCENE_CLEAR;

		isEnd_ = true;
	}

	if (world_.GetBackTitleCheck() == true) {
		next_ = SceneType::SCENE_TITLE;
		isEnd_ = true;
	}
}


void GamePlayScene::draw() const {

		Graphics3D::clear();
		//Graphics3D::clear_color(1.0f, 0.5f, 0.5f);
		//スカイボックスの描画
		Skybox::bind(0);
		Skybox::draw();
		//ステージの描画
		CollisionMesh::bind(0);
		CollisionMesh::draw();

		
		
		world_.draw();
	
		//ビルボードの描画
		Graphics3D::blend_mode(BlendMode::Add);
		//Billboard::bind(0);
		//Billboard::draw({ 0.0f,30.0f,0.0f }, 10.0f); /*10.0は大きさ*/
		Graphics3D::blend_mode(BlendMode::None);
}
void GamePlayScene::end() 
{
	Graphics3D::finalize();
}
