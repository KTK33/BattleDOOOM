#include "ShootingCamera.h"
#include "../Graphics/Graphics3D.h"

#include "../Input/GamePad/GamePad.h"
#include "../Input/KeyBoard/Keyboard.h"
#include "../Math/Vector2.h"

#include "../TPSCamera.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Texture/Sprite.h"
#include "../Actor/UIActor/PlaySceneUI/GameClearUIh.h"
#include "../Actor/UIActor/PlaySceneUI/GameOverUI.h"

ShootingCamera::ShootingCamera(IWorld * world, std::weak_ptr<Actor> m_Player) :
	Actor(world, "Camera", Vector3::Zero),
	mAimPosMove{ 0,0 },
	mplayer{m_Player},
	mplayer_{nullptr},
	malreadyGO{false}
{}

void ShootingCamera::update(float deltaTime)
{
	//プレイヤーの検索
	mplayer_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (mplayer_ == nullptr) return;

	//プレイヤーが死ぬか、ボスが死んだら終了時処理へ
	if (GameDataManager::getInstance().GetPlayerDead() == true || 
		GameDataManager::getInstance().GetDeadBossEnemy() == true)
	{
		//ゲーム終了時設定
		PlayerGameFinish();
	}
	else
	{
		//戦闘時のカメラの設定
		CameraSet(deltaTime);
	}

	//ばね
	move(position_, 1.0f, 0.2f, 0.8f);
}

void ShootingCamera::draw() const{}

void ShootingCamera::move(const Vector3 & rest_position, float stiffness, float friction, float mass)
{
	//ばねの伸び具合を計算
	const auto stretch = position_ - rest_position;
	//ばねの力を計算
	const auto force = -stiffness * stretch;
	//加速度を追加
	const auto acceleration = force / mass;
	//移動速度を計算
	velocity_ = friction * (velocity_ + acceleration);
	//座標の更新
	position_ += velocity_;
}

void ShootingCamera::CameraSet(float deltaTime)
{
	//カメラのターゲットをプレイヤーの前方向に設定
	mtarget_ = position_ + mplayer_->Getrotation().Forward() * 50;

	//カメラのポジションの設定
	position_ = Vector3(
		mplayer_->Getposition().x + 10 * mplayer_->Getrotation().Backward().x + 5 * mplayer_->Getrotation().Right().x,
		mplayer_->Getposition().y + 18,
		mplayer_->Getposition().z + 10 * mplayer_->Getrotation().Backward().z + 5 * mplayer_->Getrotation().Right().z);

	//ポーズ中ではなく、アイテムボックスを開いていないとき
	if (world_->GetPauseCheck() == false && GameDataManager::getInstance().GetItemBoxOpen() == false)
	{
		//エイム中の操作
		Aim_Input();
	}

	//ターゲットに入力情報を加算
	mtarget_.x += mplayer_->Getrotation().Right().x * mAimPosMove.x;
	mtarget_.y += mAimPosMove.y;
	mtarget_.z += mplayer_->Getrotation().Right().z * mAimPosMove.x;

	if (GameDataManager::getInstance().GetSightCheck() == true){
		//エイム中
		In_Aim();
	}
	else{
		//エイム外
		Out_Aim();
	}

	//カメラに値を設定
	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	TPSCamera::GetInstance().Target.Set(mtarget_);
	TPSCamera::GetInstance().Up.Set(Vector3::Up);
	TPSCamera::GetInstance().Update();
}

void ShootingCamera::Aim_Input()
{
	//ゲームパッドの入力数０ならキーボード操作
	if (GetJoypadNum() == 0){
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		{
			mAimPosMove.y += 1.0f * (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
		{
			mAimPosMove.y -= 1.0f* (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
		{
			mAimPosMove.x += 1.0f * (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		{
			mAimPosMove.x -= 1.0f* (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
		}
	}
	else{
		//ゲームパッドでの右スティックの操作
		mAimPosMove += GamePad::GetInstance().RightStick() * (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
	}
}

void ShootingCamera::Out_Aim()
{
	//カメラのポジションの設定
	position_ = Vector3(
		mplayer_->Getposition().x + 10 * mplayer_->Getrotation().Backward().x + 5 * mplayer_->Getrotation().Right().x,
		mplayer_->Getposition().y + 18,
		mplayer_->Getposition().z + 10 * mplayer_->Getrotation().Backward().z + 5 * mplayer_->Getrotation().Right().z);

	//ターゲットの場所を徐々に更新
	mtarget_ = Vector3::Lerp(mtarget_, position_ + mplayer_->Getrotation().Forward(), 0.1f);

	//カメラの移動範囲の制限
	mAimPosMove = Vector2::Clamp(mAimPosMove, Vector2(0, -30), Vector2(0, 30));
}

void ShootingCamera::In_Aim()
{
	//カメラのポジションの設定
	position_ = Vector3(
		mplayer_->Getposition().x + 4 * mplayer_->Getrotation().Backward().x + 2.5f * mplayer_->Getrotation().Right().x,
		mplayer_->Getposition().y + 16,
		mplayer_->Getposition().z + 4 * mplayer_->Getrotation().Backward().z + 2.5f * mplayer_->Getrotation().Right().z);

	//ターゲットの場所を徐々に更新
	mtarget_ = Vector3::Lerp(mtarget_, position_ + mplayer_->Getrotation().Forward() * 1, 0.1f);

	//プレイヤーにターゲットのポジションを渡す
	mplayer.lock()->receiveMessage(EventMessage::SIGHT_POSITION, reinterpret_cast<void*>(&mtarget_));

	//カメラの移動と一緒にプレイヤーを回転させる
	In_Aim_Rotation();

	//エイム場所の上下制限
	mAimPosMove = Vector2::Clamp(mAimPosMove, Vector2(15, -20), Vector2(15, 15));
}

void ShootingCamera::In_Aim_Rotation()
{
	float rote = 0.0f;

	//ゲームパッドの入力数０ならキーボード操作
	if (GetJoypadNum() == 0) {
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT)) 
		{
			rote = 1.0f* (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
		}
		else if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		{
			rote = -1.0f * (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
		}
	}
	else
	{
		//ゲームパッドの右スティックのX方向
		rote = GamePad::GetInstance().RightStick().x * (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
	}
	//プレイヤーに回転を渡す
	mplayer.lock()->receiveMessage(EventMessage::SIGHT_ROTATION, reinterpret_cast<void*>(&rote));
}

void ShootingCamera::PlayerGameFinish()
{
	//プレイヤーが死亡時ゲームオーバーへ、ボス死亡時ゲームクリアへ
	if (GameDataManager::getInstance().GetPlayerDead() == true)
	{
		GameOver();
	}
	else if (GameDataManager::getInstance().GetDeadBossEnemy() == true)
	{
		GameClear();
	}

	//カメラのポジションの設定
	position_ = Vector3(
		mplayer_->Getposition().x + mDeadCamera.x * mplayer_->Getrotation().Forward().x + 1 * mplayer_->Getrotation().Right().x,
		mplayer_->Getposition().y + mDeadCamera.y,
		mplayer_->Getposition().z + mDeadCamera.z * mplayer_->Getrotation().Forward().z + 1 * mplayer_->Getrotation().Right().z);

	//カメラのターゲットの設定
	mtarget_ = mplayer_->Getposition() + 10 * mplayer_->Getrotation().Forward();
}

void ShootingCamera::GameOver()
{
	//カメラが徐々に引いていくようにする
	mDeadCamera += Vector3::One * 0.25f;

	//カメラの引く範囲の制限
	mDeadCamera = Vector3::Clamp(mDeadCamera, Vector3::Zero, Vector3(100, 100, 100));

	//一度だけゲームオーバーアクターの生成
	if (!malreadyGO)
	{
		world_->add_actor(ActorGroup::GameFinishUI, new_actor<GameOverUI>(world_));
		malreadyGO = true;
	}
}

void ShootingCamera::GameClear()
{
	//カメラが徐々に引いていくようにする
	mDeadCamera += Vector3::One * 0.25f;

	//カメラの引く範囲の制限
	mDeadCamera = Vector3::Clamp(mDeadCamera, Vector3::Zero, Vector3(100, 100, 100));

	//一度だけゲームクリアアクターの生成
	if (!malreadyGO)
	{
		world_->add_actor(ActorGroup::GameFinishUI, new_actor<GameClearUI>(world_));
		malreadyGO = true;
	}
}
