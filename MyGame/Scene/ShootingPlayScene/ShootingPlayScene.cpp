#include "ShootingPlayScene.h"
#include "../ShootingPlayScene/ShootingModeManager/ShootingModeManager.h"


//�R���X�g���N�^
ShootingPlayScene::ShootingPlayScene() :world_{},
BossArleady{false}
{}

//�J�n
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
	//�X�J�C�{�b�N�X�̕`��
	Skybox::bind(0);
	Skybox::draw();
	//�X�e�[�W�̕`��
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
