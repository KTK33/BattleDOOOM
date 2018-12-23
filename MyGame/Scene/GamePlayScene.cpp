#include "GamePlayScene.h"
//#include "../Actor/Enemy/Enemy.h"
#include "../Actor/PlayerBall/Ball.h"
#include "../Actor/Player/Player.h"
#include "../Actor/TestEnemy.h"
#include "../Actor/Camera/Camera.h"
#include "../Actor/ActorGroup.h"
#include "../Fiield/Field.h"
#include "../Skybox/Skybox.h"
#include "../Mesh/CollisionMesh.h"
#include "../Billboard/Billboard.h"
#include "../Graphics/Graphics3D.h"

#include<DxLib.h>

//�R���X�g���N�^
GamePlayScene::GamePlayScene() :world_{}
{

}



//�J�n
void GamePlayScene::start() {
	world_.initialize();
	world_.add_field(new_field<Field>(0));

	world_.add_actor(ActorGroup::Player, new_actor<Player>(0,0,&world_, Vector3{ 0.0f, 0.0f,0.0f }));

	world_.add_actor(ActorGroup::Enemy, new_actor<TestEnemy>(1, &world_, Vector3{ 10.0f, 0.0f,0.0f }));
	//world_.add_actor(ActorGroup::Enemy, new_actor<Ball>(2, &world_, Vector3{ 00.0f, 0.0f,0.0f }));

	world_.add_actor(ActorGroup::System, new_actor<Camera>(&world_));
}

void GamePlayScene::update(float deltaTime)
{
	world_.update(deltaTime);

	//if (CheckHitKey(KEY_INPUT_G))
	//{
	//	world_.add_actor(ActorGroup::Enemy, new_actor<Enemy>(1, Vector3{ 20.0f,0.0f,0.0f }, world_));
	//}

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
		
		DrawFormatString(500, 200, GetColor(255, 0, 0),  "�ړ��@�@:WASD");
		DrawFormatString(500, 220, GetColor(255, 0, 0),  "�p���`�@:B(V)");
		DrawFormatString(500, 240, GetColor(255, 0, 0),  "�L�b�N�@:X(B)");
		DrawFormatString(500, 260, GetColor(255, 0, 0),  "���@�@�@:Y(N)");
		DrawFormatString(500, 280, GetColor(255, 0, 0),  "�e�@�@�@:R3(R)");
		DrawFormatString(500, 300, GetColor(255, 0, 0), "�W�����v :A(U)");
		DrawFormatString(500, 320, GetColor(255, 0, 0), "��]     :RBLB(LR)");
	
}
void GamePlayScene::end() 
{
	Graphics3D::finalize();
}
