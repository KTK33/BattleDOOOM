#include "GamePlayScene.h"
//#include "../Actor/Enemy/Enemy.h"
#include "../Actor/PlayerBall/Ball.h"
#include "../Actor/Player/Player.h"
#include "../Actor/Enemy/TestEnemy.h"
#include "../Actor/Enemy/DummyEnemy.h"
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

#include<DxLib.h>

//�R���X�g���N�^
GamePlayScene::GamePlayScene() :world_{}
{

}



//�J�n
void GamePlayScene::start() {
	world_.initialize();
	GameDataManager::getInstance().initialize();

	//world_.add_field(new_field<Field>(0));


	world_.add_actor(ActorGroup::Player, new_actor<Player>(0,0,&world_, Vector3{ 0.0f, 0.0f,0.0f }));

	world_.add_actor(ActorGroup::Enemy, new_actor<TestEnemy>(1, &world_, Vector3{ 10.0f, 0.0f,0.0f }));

	for (int i = 0; i < 10; i++)
	{
		world_.add_actor(ActorGroup::Enemy, new_actor<DummyEnemy>(1, &world_, Vector3{ Random::rand(0.0f,150.0f), 0.0f,Random::rand(0.0f,150.0f) }));
	}
	world_.add_actor(ActorGroup::System, new_actor<Camera>(&world_));

	world_.add_actor(ActorGroup::UI, new_actor<EnemyDeadText>(&world_));

	world_.add_actor(ActorGroup::UI, new_actor<AnyUI>(&world_));

	PauseCheck = false;
}

void GamePlayScene::update(float deltaTime)
{
	if (!PauseCheck)
	{
		world_.update(deltaTime);
		GameDataManager::getInstance().update();
	}

	//if (world_.find_actor(ActorGroup::Enemy, "Enemy") == NULL) {
	//	world_.add_actor(ActorGroup::Enemy, new_actor<TestEnemy>(1, &world_, 
	//		Vector3{ Random::rand(0.0f,300.0f), 0.0f,Random::rand(0.0f,300.0f)}));
	//}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM8))
	{
		Pause();
	}
}


void GamePlayScene::draw() const {

		Graphics3D::clear();
		//Graphics3D::clear_color(1.0f, 0.5f, 0.5f);
		//�X�J�C�{�b�N�X�̕`��
		Skybox::bind(0);
		Skybox::draw();
		//�X�e�[�W�̕`��
		CollisionMesh::bind(0);
		CollisionMesh::draw();
		
		world_.draw();
	
		//�r���{�[�h�̕`��
		Graphics3D::blend_mode(BlendMode::Add);
		Billboard::bind(0);
		Billboard::draw({ 0.0f,30.0f,0.0f }, 10.0f); /*10.0�͑傫��*/
		Graphics3D::blend_mode(BlendMode::None);

		if (PauseCheck){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(0, 0, 1960, 1080, GetColor(255, 255, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			SetFontSize(64);
			DrawFormatString(500, 200, GetColor(255, 0, 0), "�ړ��@�@:WASD");
			DrawFormatString(500, 280, GetColor(255, 0, 0), "�p���`�@:B(V)");
			DrawFormatString(500, 360, GetColor(255, 0, 0), "�L�b�N�@:X(B)");
			DrawFormatString(500, 440, GetColor(255, 0, 0), "���@�@�@:Y(N)");
			DrawFormatString(500, 520, GetColor(255, 0, 0), "�e�@�@�@:R3(R)");
			DrawFormatString(500, 600, GetColor(255, 0, 0), "�W�����v :A(U)");
			DrawFormatString(500, 680, GetColor(255, 0, 0), "��]     :RBLB(LR)");
			SetFontSize(16);
		}
}
void GamePlayScene::end() 
{
	Graphics3D::finalize();
}

void GamePlayScene::Pause()
{
	if(!PauseCheck) PauseCheck = true;
	else PauseCheck = false;
}
