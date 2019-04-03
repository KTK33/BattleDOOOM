#include "GamePlayScene.h"
#include "../Actor/PlayerBall/Ball.h"
#include "../Actor/Player/Player.h"
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
#include "../Input/Keyboard.h"
#include "../Texture/Sprite.h"
#include "../Game/Define.h"
#include "../Actor/UIActor/AnyUI.h"
#include "../Actor/UIActor/PlayerTextUI.h"
#include "../Actor/UIActor/Pause.h"
#include "../Actor/UIActor/FadeUI.h"
#include "../Actor/UIActor/PlaySceneUI/GameClearUIh.h"
#include "../Sound/Sound.h"

#include<DxLib.h>

//コンストラクタ
GamePlayScene::GamePlayScene() :world_{}
{

}



//開始
void GamePlayScene::start() {
	world_.initialize();
	GameDataManager::getInstance().initialize();

	Sound::GetInstance().PlayBGM(BGM_ID::PLAYE_BGM, DX_PLAYTYPE_LOOP);
	//Sound::GetInstance().SetBGMVolume(BGM_ID::PLAYE_BGM, 1.0f);
	menuSize_ = 4;
	BossArleady = false;

	world_.add_actor(ActorGroup::Fade, new_actor<FadeUI>(&world_, 1, 2));

	auto P_Text = new_actor<PlayerTextUI>(&world_);
	world_.add_actor(ActorGroup::UI, P_Text);

	auto P = new_actor<Player>(0, 1, &world_, Vector3{ 0.0f, -20.0f,0.0f }, P_Text);
	world_.add_actor(ActorGroup::Player, P);

	auto ANYUI = new_actor<AnyUI>(&world_,P);
	world_.add_actor(ActorGroup::UI, ANYUI);

	world_.add_actor(ActorGroup::PauseUI, new_actor<PauseUI>(&world_));

	auto dummy1 = new_actor<DummyEnemy>(11, &world_, Vector3{ Random::rand(-200.0f,60.0f), -20.0,Random::rand(-200.0f,60.0f) }, Matrix::CreateRotationY(Random::rand(0.0f,360.0f)), ANYUI);
	world_.add_actor(ActorGroup::Enemy,dummy1);

	auto dummy2 = new_actor<DummyEnemy>(12, &world_, Vector3{ Random::rand(-200.0f,60.0f), -20.0,Random::rand(-200.0f,60.0f) }, Matrix::CreateRotationY(Random::rand(0.0f, 360.0f)), ANYUI);
	world_.add_actor(ActorGroup::Enemy, dummy2);

	auto dummy3 = new_actor<DummyEnemy>(13, &world_, Vector3{ Random::rand(-200.0f,60.0f), -20.0,Random::rand(-200.0f,60.0f) }, Matrix::CreateRotationY(Random::rand(0.0f, 360.0f)), ANYUI);
	world_.add_actor(ActorGroup::Enemy, dummy3);


	world_.add_actor(ActorGroup::System, new_actor<Camera>(&world_,P));

}

void GamePlayScene::update(float deltaTime)
{
	world_.update(deltaTime);

	if (world_.find_actor(ActorGroup::Enemy, "DummyEnemy") == NULL && BossArleady == false)
	{
		world_.add_actor(ActorGroup::Enemy, new_actor<BossEnemy>(3, &world_, Vector3{ 20.0f, -35.0f,20.0f }));
		BossArleady = true;
	}


	if (GameDataManager::getInstance().GetPlayerDead() == true)
	{
		if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM2) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
		{
			next_ = SceneType::SCENE_TITLE;
			isEnd_ = true;
		}
	}

	if (GameDataManager::getInstance().GetDeadBossEnemy() == true) {

		if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM2) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
		{
			next_ = SceneType::SCENE_TITLE;
			isEnd_ = true;
		}
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
