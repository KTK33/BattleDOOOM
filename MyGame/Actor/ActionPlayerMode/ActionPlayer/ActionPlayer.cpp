#include "ActionPlayer.h"
#include "../Actor/PlayerBullet/PlayerBullet.h"
#include "../../ActorGroup.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
#include "../Texture/Sprite.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Actor/PlayerAttackCollision/PlayerAttackCollision.h"
#include "../Actor/Player/PlayerItemBox/PlayerItemBox.h"
#include "ActionPlayerMotionNum.h"

ActionPlayer::ActionPlayer(int model, int weapon, IWorld * world, const Vector3 & position, std::weak_ptr<Actor> ui, const IBodyPtr & body) :
	Actor(world, "Player", position, body),
	Initbody{ body },
	m_ui{ ui },
	mesh_{ model,weapon },
	weapon_{ weapon },
	state_{ ActionPlayerState::ActionPlayerIdel },
	before_state_{ ActionPlayerState::NONE },
	state_timer_{ 0.0f },
	mRightweaponPos{ 15 },
	mLeftweaponPos{ 38 },
	invinciblyCheck{ false },
	invinciblyTime{ 100 },
	DeadCheck{ false },
	m_ActionCameraForward{ 0 },
	m_ActionCameraRight{ 0 }
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());
	hp_ = PlayerHP;

	ActorSystem::TransparenceInit();

	velocity_ = Vector3::Zero;

	mAttackCount = 0;
}

void ActionPlayer::initialize()
{
}

void ActionPlayer::update(float deltaTime)
{
	if (world_->GetPauseCheck() == false
		&& GameDataManager::getInstance().GetDeadBossEnemy() == false) {
		if (!DeadCheck)
		{
			mesh_.update(deltaTime);
			mesh_.transform(Getpose());
			Motion(deltaTime);
			if (state_ == ActionPlayerState::ActionPlayerIdel)
			{
				Idle();
			}
			mesh_.change_motion(motion_);
			Delay();
		}
	}

	world_->send_message(EventMessage::PLAYER_HP, (void*)&hp_);

	hp_ = MathHelper::Clamp(hp_, 0, 10);

	//velocity_ = Vector3::Zero;
	velocity_ += Vector3::Up * -gravity;
	position_ += velocity_;

	velocity_ *= 0.8f;
	if (velocity_.Length() < 0.01f) {
		velocity_ = 0.0f;
	}

	collision();
	if (Floorcollide) gravity = 0.0f;
	else gravity = 9.8f*0.1f;

	if (invinciblyCheck) {
		ActorTransparence();
	}
	else {
		TransparenceInit();
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3))
	{
		mRightweaponPos += 1;
	}
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM4))
	{
		mRightweaponPos -= 1;
	}
}

void ActionPlayer::draw() const
{
	mesh_.draw();
	draw_weapon();

	DrawFormatString(500, 450, GetColor(255, 255, 255), "%f", state_timer_);
	DrawFormatString(500, 500, GetColor(255, 255, 255), "%f", mesh_.motion_end_time());
	DrawFormatString(500, 400, GetColor(255, 255, 255), "%i", motion_);


	DrawFormatString(500, 400, GetColor(255, 0, 255), "%i", mRightweaponPos);

	if(mAttackcheck)
	DrawFormatString(600, 600, GetColor(255, 255, 255), "B");
}

void ActionPlayer::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER, (void*)&hitdir);
}

void ActionPlayer::receiveMessage(EventMessage message, void * param)
{
	if (!invinciblyCheck)
	{
		if (message == EventMessage::HIT_ENEMY_BULLET)
		{
			hp_ = hp_ - *(int*)param;
			change_state(ActionPlayerState::ActionPlayerDamage, ActionPlayerMotion::Motion::MotionPlayerIdel);
			invinciblyCheck = true;
		}
	}

	if (message == EventMessage::PLAYER_HP)
	{
		*(int*)param = hp_;
	}

	if (message == EventMessage::HIT_ENEMY)
	{
		Hit(*(Vector3*)param);
	}

	if (message == EventMessage::ACTION_CAMERA_FORWARD)
	{
		m_ActionCameraForward = *(Vector3*)param;
	}
	if (message == EventMessage::ACTION_CAMERA_RIGHT)
	{
		m_ActionCameraRight = *(Vector3*)param;
	}
}

void ActionPlayer::collision()
{
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		position_.x = result.x;
		position_.z = result.z;
		Stagecollide = true;
	}
	else{
		Stagecollide = false;
	}

	//床との接地判定
	if (floor(result)) {
		if (state_ != ActionPlayerState::State::ActionPlayerJump){
			Floorcollide = true;
			position_ = result + rotation_.Up()*(body_->length()*0.5f + body_->radius()*0.5f);
		}
	}
	else {
		Floorcollide = false;
	}
}

void ActionPlayer::change_state(ActionPlayerState::State state, int motion)
{
	before_motion_ = motion_;
	motion_ = motion;
	before_state_ = state_;
	state_ = state;
	state_timer_ = 0.0f;
}

void ActionPlayer::Idle()
{
	Move(GamePad::GetInstance().Stick());

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2))
	{
		change_state(ActionPlayerState::ActionPlayerAttack, ActionPlayerMotion::Motion::MotionPlayerAttack1);
	}

	mAttackCount = 0;
	mAttackcheck = false;
}

void ActionPlayer::Move(Vector2 input)
{
	//スティックを倒していないときはアイドル
	if (input.x == 0.0f && input.y == 0.0f){
		change_state(ActionPlayerState::ActionPlayerIdel, ActionPlayerMotion::Motion::MotionPlayerIdel);
		return;
	}
	Movement(0.5f, input);
	//Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::WALKSTEP_SE);
}

void ActionPlayer::Movement(float spped, Vector2 input)
{
	//前後左右移動
	velocity_ = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };
	float yaw_speed{ 0.0f };

	side_speed = -input.x * spped;
	forward_speed = input.y * spped;

	//カメラの前方方向を前方向とする
	velocity_ += m_ActionCameraForward * forward_speed;
	velocity_ += -m_ActionCameraRight * side_speed;

	//回避コマンド
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1)){
		change_state(ActionPlayerState::ActionPlayerAvoidance, ActionPlayerMotion::Motion::MotionPlayerAvoidance);
	}

	//回避加速度
	static const int mAvoidanceSpeed = 15.0f;
	
	//ダッシュ加速
	float DashSpped = 0.0f;

	if (state_ == ActionPlayerState::ActionPlayerAvoidance)
	{
		velocity_ += velocity_ * mAvoidanceSpeed;
	}
	else
	{
		//スティックの倒し具合で走るモーション
		if (MathHelper::Abs(input.x) >= 0.8f || MathHelper::Abs(input.y) >= 0.8f)
		{
			motion_ = ActionPlayerMotion::MotionPlayerRun;
			DashSpped = 0.5f;
		}
		else
		{
			motion_ = ActionPlayerMotion::MotionPlayerWalk;
		}
	}

	position_ += velocity_ * (1.0f + DashSpped);
	
	//進んでいる方向に向く
	Vector3 angle = m_ActionCameraForward * input.y + m_ActionCameraRight * input.x;
	angle.y = 0.0f;
	Matrix to_Target_rotate = Matrix::CreateLookAt(position_, position_ + angle.Normalize(), Vector3::Up);
	rotation_ = Matrix::Lerp(rotation_, Matrix::Invert(to_Target_rotate) * Matrix::CreateRotationY(180),0.1f);
}

void ActionPlayer::Avoidance()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		change_state(ActionPlayerState::ActionPlayerIdel, ActionPlayerMotion::Motion::MotionPlayerIdel);
	}
}

void ActionPlayer::Attack()
{
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1)){
		change_state(ActionPlayerState::ActionPlayerAvoidance, ActionPlayerMotion::Motion::MotionPlayerAvoidance);
	}

	if (state_timer_ > mesh_.motion_end_time() - 20)
	{
		mAttackcheck = true;
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2))
		{
			mAttackCount += 1;
			mAttackcheck = false;
			switch (mAttackCount)
			{
			case 1:
				change_state(ActionPlayerState::ActionPlayerAttack, ActionPlayerMotion::Motion::MotionPlayerAttack2);
				break;
			case 2:
				change_state(ActionPlayerState::ActionPlayerAttack, ActionPlayerMotion::Motion::MotionPlayerAttack3);
				break;
			default:
				break;
			}
		}
	}
}

void ActionPlayer::Motion(float deltaTime)
{
	state_timer_ += deltaTime/2;

	if (state_ == ActionPlayerState::ActionPlayerAttack){
		Attack();
	}

	if (state_timer_ > mesh_.motion_end_time()-5)
	{
		switch (state_){
		case ActionPlayerState::State::ActionPlayerAttack:
			change_state(ActionPlayerState::ActionPlayerIdel, ActionPlayerMotion::Motion::MotionPlayerIdel);
			break;
		case ActionPlayerState::State::ActionPlayerAvoidance:
			change_state(ActionPlayerState::ActionPlayerIdel, ActionPlayerMotion::Motion::MotionPlayerIdel);
			break;
		case ActionPlayerState::State::ActionPlayerDamage:
			change_state(ActionPlayerState::ActionPlayerIdel, ActionPlayerMotion::Motion::MotionPlayerIdel);
			break;
		case ActionPlayerState::State::ActionPlayerDead:
			DeadCheck = true;
			break;
		default: break;
		};
	}
}

void ActionPlayer::draw_weapon() const
{
	StaticMesh::bind(weapon_);
	StaticMesh::transform(mesh_.bone_matrix(mRightweaponPos));
	StaticMesh::draw();

	StaticMesh::bind(weapon_);
	StaticMesh::transform(mesh_.bone_matrix(mLeftweaponPos));
	StaticMesh::draw();

}

void ActionPlayer::Delay()
{
	if (invinciblyCheck) {
		if (hp_ > 0)
		{
			invinciblyTime--;
			if (invinciblyTime <= 0)
			{
				invinciblyCheck = false;
				invinciblyTime = 100;
			}
		}
		else {
			motion_ = ActionPlayerMotion::Motion::MotionPlayerIdel;
			state_ = ActionPlayerState::ActionPlayerDead;
			GameDataManager::getInstance().SetPlayerDead(true);
		}
	}
}

void ActionPlayer::Hit(Vector3 & dir)
{
	Vector3 dir_ = Vector3::Normalize(dir);
	//アクターからプレイヤーの方向に移動
	velocity_ = Vector3::Up * 7.0f + Vector3{ dir_.x,0.f,dir_.z } *2.0f;
	velocity_.x = Vector3::Up.x * 7.0f + dir_.x*2.0f;
	velocity_.z = Vector3::Up.z * 7.0f + dir_.z*2.0f;
	velocity_.y = 0.0f;
	//collide = true;
}
