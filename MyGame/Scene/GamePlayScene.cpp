#include "GamePlayScene.h"
//#include "../Actor/Enemy/Enemy.h"
#include "../Actor/PlayerBall/Ball.h"
#include "../Actor/Player/Player.h"
#include "../Actor/TestEnemy.h"
#include "../Actor/ActorGroup.h"
#include "../Fiield/Field.h"
#include "../Skybox/Skybox.h"
#include "../Mesh/CollisionMesh.h"
#include "../Billboard/Billboard.h"
#include "../Graphics/Graphics3D.h"

#include "../Actor/Camera/Camera.h"

#include<DxLib.h>

//コンストラクタ
GamePlayScene::GamePlayScene() :world_{}
{

}



//開始
void GamePlayScene::start() {
	world_.initialize();
	world_.add_field(new_field<Field>(0));

//	world_.add_actor(ActorGroup::Player, new_actor<Player>(0,0,world_, Vector3{ 0.0f,0.0f,0.0f }));
//
//	world_.add_actor(ActorGroup::Enemy, new_actor<Enemy>(0, Vector3{ 20.0f,0.0f,0.0f }, world_));
//	
//	//world_.add_actor(ActorGroup::Ball, new_actor<Ball>(1,world_, Vector3{ 30.0f,30.0f,0.0f }));
//
//	world_.add_actor(ActorGroup::System, new_actor<Camera>(world_, Vector3{ 0.0f,0.0f,0.0f }));

	world_.add_actor(ActorGroup::Player, new_actor<Player>(0,0,&world_, Vector3{ 0.0f, 0.0f,0.0f }));

	world_.add_actor(ActorGroup::Enemy, new_actor<TestEnemy>(1, &world_, Vector3{ 10.0f, 0.0f,0.0f }));
	//world_.add_actor(ActorGroup::Enemy, new_actor<Ball>(2, &world_, Vector3{ 00.0f, 0.0f,0.0f }));
}

void GamePlayScene::update(float deltaTime)
{
	world_.update(deltaTime);
	//ダメージのテスト
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		//player_->react();
		//enemy_->react();
	}

	//if (CheckHitKey(KEY_INPUT_G))
	//{
	//	world_.add_actor(ActorGroup::Enemy, new_actor<Enemy>(1, Vector3{ 20.0f,0.0f,0.0f }, world_));
	//}

}


void GamePlayScene::draw() const {

		Graphics3D::clear();
		//Graphics3D::clear_color(1.0f, 0.5f, 0.5f);
		//カメラの設定
		Graphics3D::view_matrix(Matrix::CreateLookAt({ 0.0f,46.0f,80.0f },
			{ 0.0f,31.0f,0.0f }, { 0.0f,2.0f,5.0f }));
		Graphics3D::projection_matrix(Matrix::CreatePerspectiveFieldOfView(
			49.0f, 640.0f / 480.0f, 0.3f, 1000.0f));
		//スカイボックスの描画
		Skybox::bind(0);
		Skybox::draw();
		//ステージの描画
		CollisionMesh::bind(0);
		CollisionMesh::draw();
		
		world_.draw();
	
		//ビルボードの描画
		Graphics3D::blend_mode(BlendMode::Add);
		Billboard::bind(0);
		Billboard::draw({ 0.0f,30.0f,0.0f }, 10.0f); /*10.0は大きさ*/
		Graphics3D::blend_mode(BlendMode::None);
		
		DrawFormatString(500, 200, GetColor(255, 0, 0),  "移動　　:方向キー");
		DrawFormatString(500, 220, GetColor(255, 0, 0),  "パンチ　:B(Q)");
		DrawFormatString(500, 240, GetColor(255, 0, 0),  "キック　:X(W)");
		DrawFormatString(500, 260, GetColor(255, 0, 0),  "剣　　　:Y(E)");
		DrawFormatString(500, 280, GetColor(255, 0, 0),  "銃　　　:R3(R)");
		DrawFormatString(500, 300, GetColor(255, 0, 0), "ジャンプ :A(U)");
		DrawFormatString(500, 320, GetColor(255, 0, 0), "回転     :RBLB(YT)");
	
}
void GamePlayScene::end() 
{
	Graphics3D::finalize();
}
