#include "ShootingPlayScene.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/ShootingPlayerActor.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/NormalEnemy/NormalEnemyActor.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BossEnemy/BossEnemyActor.h"
#include "../Actor/ShootingPlayerMode/ShootingCamera/ShootingCamera.h"
#include "../Actor/ActorGroup.h"
#include "../Fiield/Field.h"
#include "../Skybox/Skybox.h"
#include "../Mesh/CollisionMesh.h"
#include "../Billboard/Billboard.h"
#include "../Graphics/Graphics3D.h"
#include "../Fiield/WorldContentManager/WorldContentManager.h"
#include "../GameData/GameDataManager.h"
#include "../Input/InputInfoInc.h"
#include "../Texture/Sprite.h"
#include "../Game/Define.h"
#include "../Actor/ShootingPlayerMode/UIActor/AnyUI/AnyUI.h"
#include "../Actor/ShootingPlayerMode/UIActor/ShootingPlayerTextUI/ShootingPlayerTextUI.h"
#include "../Actor/ShootingPlayerMode/UIActor/Pause/Pause.h"
#include "../Actor/ShootingPlayerMode/UIActor/PlaySceneUI/GameClearUIh.h"
#include "../Actor/CommonUIActor/FadeUI/FadeUI.h"
#include "../Sound/Sound.h"

#include<DxLib.h>

//コンストラクタ
ShootingPlayScene::ShootingPlayScene() :world_{},
BossArleady{false}
{}

//開始
void ShootingPlayScene::start() {
	world_.initialize();
	GameDataManager::getInstance().initialize();
	Sound::GetInstance().PlayBGM(BGM_ID::PLAYE_BGM, DX_PLAYTYPE_LOOP);
	menuSize_ = 4;

	world_.add_actor(ActorGroup::Fade, new_actor<FadeUI>(&world_, 1, 2));

	auto P_Text = new_actor<ShootingPlayerTextUI>(&world_);
	world_.add_actor(ActorGroup::UI, P_Text);

	auto P = new_actor<ShootingPlayerActor>(0, 1, &world_, Vector3{ 0.0f, 30.0f,0.0f }, P_Text);
	world_.add_actor(ActorGroup::Player, P);

	auto ANYUI = new_actor<AnyUI>(&world_);
	world_.add_actor(ActorGroup::UI, ANYUI);

	world_.add_actor(ActorGroup::PauseUI, new_actor<PauseUI>(&world_));

	auto dummy1 = new_actor<NormalEnemyActor>(11, &world_, Vector3{ 20.0f, 30.0f,  -150.0f }, Matrix::CreateRotationY(Random::rand(0.0f, 360.0f)));
	world_.add_actor(ActorGroup::Enemy, dummy1);

	auto dummy2 = new_actor<NormalEnemyActor>(12, &world_, Vector3{ 130.0f, 30.0f, -4.0f }, Matrix::CreateRotationY(Random::rand(0.0f, 360.0f)));
	world_.add_actor(ActorGroup::Enemy, dummy2);

	auto dummy3 = new_actor<NormalEnemyActor>(13, &world_, Vector3{ -110.0f , 30.0f, 90.0f }, Matrix::CreateRotationY(Random::rand(0.0f, 360.0f)));
	world_.add_actor(ActorGroup::Enemy, dummy3);


	world_.add_actor(ActorGroup::System, new_actor<ShootingCamera>(&world_,P));

}

void ShootingPlayScene::update(float deltaTime)
{
	world_.update(deltaTime);

	if (world_.find_actor(ActorGroup::Enemy, "NormalEnemy") == NULL && BossArleady == false)
	{
		world_.add_actor(ActorGroup::BossEnemy, new_actor<BossEnemyActor>(3, &world_, Vector3{ 200.0f, 30.0f,20.0f }));
		BossArleady = true;
	}


	if (GameDataManager::getInstance().GetPlayerDead()
		|| GameDataManager::getInstance().GetDeadBossEnemy()
		|| world_.GetBackTitleCheck() == true)
	{
		if (ButtonB::GetInstance().TriggerDown())
		{
			next_ = SceneType::SCENE_TITLE_LOAD;
			isEnd_ = true;
			return;
		}
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
}
void ShootingPlayScene::end()
{
	Graphics3D::finalize();
	CollisionMesh::finalize();
	Skybox::finalize();
	Sound::GetInstance().Initialize();
	Sprite::GetInstance().Initialize();
}
