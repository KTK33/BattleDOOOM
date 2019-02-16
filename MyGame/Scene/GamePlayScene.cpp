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

	world_.add_field(new_field<Field>(0));

	auto P_Box = new_actor<PlayerItemBox>(&world_);
	world_.add_actor(ActorGroup::Player, P_Box);

	auto P = new_actor<Player>(0, 0, &world_, Vector3{ 0.0f, 0.0f,0.0f },P_Box);
	world_.add_actor(ActorGroup::Player, P);

	world_.add_actor(ActorGroup::UI, new_actor<AnyUI>(&world_,P));

	//world_.add_actor(ActorGroup::Enemy, new_actor<Enemy>(4, &world_, Vector3{ 10.0f, 0.0f,0.0f }));

	for (int i = 0; i < 5; i++)
	{
		auto dummy = new_actor<DummyEnemy>(1, &world_, Vector3{ Random::rand(0.0f,70.0f), 0.0f,Random::rand(0.0f,70.0f) }, Matrix::CreateRotationY(Random::rand(0.0f,360.0f)));
		world_.add_actor(ActorGroup::Enemy,dummy);
	}

	world_.add_actor(ActorGroup::Enemy, new_actor<BossEnemy>(3, &world_, Vector3{ 10.0f, 0.0f,0.0f }));

	//world_.add_actor(ActorGroup::Enemy, new_actor<ExEnemy>(10, &world_, Vector3{ 20.0f, 0.0f,0.0f }));

	world_.add_actor(ActorGroup::System, new_actor<Camera>(&world_));

	world_.add_actor(ActorGroup::UI, new_actor<EnemyDeadText>(&world_));

	PauseCheck = false;
}

void GamePlayScene::update(float deltaTime)
{
	if (!PauseCheck)
	{
		world_.update(deltaTime);
		GameDataManager::getInstance().update();
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM8))
	{
		PauseCheck = !PauseCheck;
	}

	if (PauseCheck){
		Pause();
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

	//if (GamePad::GetInstance().ButtonStateDown(PADBUTTON::DOWN))
	//{
	//	GameDataManager::getInstance().SetItemBoxCheck(true);
	//}
	//else
	//{
	//	GameDataManager::getInstance().SetItemBoxCheck(false);
	//}
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

		if (PauseCheck){
			Sprite::GetInstance().Draw(SPRITE_ID::PAUSEBACK, Vector2(0, (float)WINDOW_HEIGHT));
		}
}
void GamePlayScene::end() 
{
	Graphics3D::finalize();
}

void GamePlayScene::Pause()
{
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
	{
		PauseCheck = false;
	}

}
