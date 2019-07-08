#include "ShootingTPSCamera.h"
#include "../Input/InputInfoInc.h"
#include "../Math/Vector2.h"

#include "../Actor/Camera/CameraSpring/CameraSpring.h"
#include "../Actor/Camera/TPSCamera.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Texture/Sprite.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/ShootingPlayerParam/ShootingPlayerParam.h"
#include "../Actor/ShootingPlayerMode/UIActor/PlaySceneUI/GameClearUIh.h"
#include "../Actor/ShootingPlayerMode/UIActor/PlaySceneUI/GameOverUI.h"


ShootingTPSCamera::ShootingTPSCamera(IWorld * world, std::weak_ptr<Actor> m_Player) :
	Actor(world, "ActionCamera", Vector3::Zero),
	m_player{ m_Player },
	player_{ nullptr },
	m_Offset(-30.0f, 0.0f, 0.0f),
	m_Up(Vector3::UnitY),
	m_PitchSpeed(0.0f),
	m_YawSpeed(0.0f),
	mFinishCamera{ 20.0f,20.0f,20.0f },
	malreadyCreate{ false }
{}

void ShootingTPSCamera::update(float deltaTime)
{
	prevPosition_ = position_;
	//プレイヤーの検索
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	if (GameDataManager::getInstance().GetDeadBossEnemy() ||
		GameDataManager::getInstance().GetPlayerDead())
	{
		//ゲーム終了時設定
		PlayerGameFinish();
	}
	else
	{
		PlayerInput(deltaTime);
	}
	//ばね
	CameraSpring::move(position_, velocity_, prevPosition_, 1.0f, 0.2f, 0.8f);
}

void ShootingTPSCamera::draw() const {
	//照準の描画
	mSU.draw();

	//カメラに値を設定
	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	TPSCamera::GetInstance().Target.Set(target_);
	TPSCamera::GetInstance().Up.Set(m_Up);
	TPSCamera::GetInstance().Update();
}

void ShootingTPSCamera::PlayerInput(float deltaTime)
{
	m_YawSpeed = RightStick::GetInstance().GetAngle().x;
	m_PitchSpeed = -RightStick::GetInstance().GetAngle().y;

	//上下の上限の制御
	if (GetCameraAngleVRotate() >= 0.4f) {
		m_PitchSpeed = -0.1f;
	}
	else if (GetCameraAngleVRotate() <= -0.4f) {
		m_PitchSpeed = 0.1f;
	}

	//ポーズ中とアイテムボックスを開いている時にはカメラは動かなせない
	if (world_->GetPauseCheck() || 
		ShootingPlayerParam::getInstance().Get_ItemBoxOpen()) return;

	//ワールド上方を軸とするヨーのクォータニオンを作成
	const Quaternion yaw(Vector3::UnitY, m_YawSpeed * deltaTime);
	//カメラのオフセットと上方ベクトルをヨーで変換
	m_Offset = Quaternion::Transform(m_Offset, yaw);
	m_Up = Quaternion::Transform(m_Up, yaw);

	//カメラの前方/右方向を計算
	Vector3 forward = -1.0f * m_Offset;
	forward.Normalize();
	Vector3 right = Vector3::Cross(m_Up, forward);
	right.Normalize();

	//カメラ右方向を軸とするピッチのクォータニオンを作成
	const Quaternion pitch(right, m_PitchSpeed * deltaTime);
	//カメラのオフセットと上方ベクトルをピッチで変換
	m_Offset = Quaternion::Transform(m_Offset, pitch);
	m_Up = Quaternion::Transform(m_Up, pitch);

	target_ = player_->Getposition() + right * 5.0f;
	target_.y = target_.y + PlayerHeight;

	float dis = 0.0f;

	//プレイヤーがエイム中か
	if (ShootingPlayerParam::getInstance().Get_AimCheck()) {
		//エイム中
		dis = MathHelper::Lerp(dis, 1.5f, 0.1f);
	}
	else {
		//エイム外
		dis = MathHelper::Lerp(dis, 8.0f, 0.1f);
	}

	position_ = target_ + m_Offset * dis;
 
	//照準の位置をセットする
	Vector3 to_Target = position_ + forward.Normalize();
	ShootingPlayerParam::getInstance().Set_AimPos(to_Target);

	//プレイヤーにカメラの前方向を渡す
	m_player.lock()->receiveMessage(EventMessage::SIGHT_ROTATION, reinterpret_cast<void*>(&forward));

	mSU.SetAimPos(GetCameraTarget(), ShootingPlayerParam::getInstance().Get_AimCheck());
}

void ShootingTPSCamera::receiveMessage(EventMessage message, void * param)
{}

void ShootingTPSCamera::PlayerGameFinish()
{
	//プレイヤーが死亡時ゲームオーバーへ、ボス死亡時ゲームクリアへ
	if (GameDataManager::getInstance().GetPlayerDead() == true)
	{
		NextSceneType(0);
	}
	else if (GameDataManager::getInstance().GetDeadBossEnemy() == true)
	{
		NextSceneType(1);
	}

	//カメラのポジションの設定
	position_ = Vector3(
		player_->Getposition().x + mFinishCamera.x * player_->Getrotation().Forward().x + player_->Getrotation().Right().x,
		player_->Getposition().y + mFinishCamera.y,
		player_->Getposition().z + mFinishCamera.z * player_->Getrotation().Forward().z + player_->Getrotation().Right().z);

	//カメラのターゲットの設定
	target_ = player_->Getposition() + 10 * player_->Getrotation().Forward();
}

void ShootingTPSCamera::NextSceneType(int type)
{
	//カメラが徐々に引いていくようにする
	mFinishCamera += Vector3::One * 0.25f;

	//カメラの引く範囲の制限
	mFinishCamera = Vector3::Clamp(mFinishCamera, Vector3::Zero, Vector3(100, 100, 100));

	//一度だけゲームクリアアクターの生成
	if (!malreadyCreate)
	{
		if (type == 0)
		{
			world_->add_actor(ActorGroup::GameFinishUI, new_actor<GameOverUI>(world_));
		}
		else if (type == 1)
		{
			world_->add_actor(ActorGroup::GameFinishUI, new_actor<GameClearUI>(world_));
		}
		malreadyCreate = true;
	}
}