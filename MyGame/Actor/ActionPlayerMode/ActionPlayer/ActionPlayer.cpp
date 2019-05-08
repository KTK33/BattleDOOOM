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
	DeadCheck{ false },
	m_ActionCameraForward{ 0 },
	m_ActionCameraRight{ 0 },
	mweaponalready{false}
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
	collision();

	if ((world_->GetPauseCheck() == true && GameDataManager::getInstance().GetDeadBossEnemy() == true) || DeadCheck) return;

	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	Motion(deltaTime);
	Idle();
	mesh_.change_motion(motion_);

	world_->send_message(EventMessage::PLAYER_HP, (void*)&hp_);

	hp_ = MathHelper::Clamp(hp_, 0, 10);

	//velocity_ = Vector3::Zero;
	velocity_ += Vector3::Up * -gravity;
	position_ += velocity_;

	velocity_ *= 0.8f;
	if (velocity_.Length() < 0.01f) {
		velocity_ = 0.0f;
	}

	if (Floorcollide) gravity = 0.0f;
	else gravity = 9.8f*0.1f;

	if (hp_ <= 0)
	{
		GameDataManager::getInstance().SetPlayerDead(true);
		DeadCheck = true;
	}
}

void ActionPlayer::draw() const
{
	mesh_.draw();
	draw_weapon();

	//if(mAttackcheck)
	//DrawFormatString(600, 600, GetColor(0, 0, 255), "B");

	//SetFontSize(32);
	//DrawFormatString(200, 450, GetColor(0, 0, 255), "%f", position_.x);
	//DrawFormatString(200, 550, GetColor(0, 0, 255), "%f", position_.y);
	//DrawFormatString(200, 650, GetColor(0, 0, 255), "%f", position_.z);
	//DrawFormatString(200, 700, GetColor(0, 0, 255), "%i", mAttackCount);
	//SetFontSize(16);

}

void ActionPlayer::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER, (void*)&hitdir);
}

void ActionPlayer::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_ENEMY_BULLET)
	{
		hp_ = hp_ - *(int*)param;
		change_state(ActionPlayerState::ActionPlayerDamage, ActionPlayerMotion::Motion::MotionPlayerIdel);
	}

	if (message == EventMessage::PLAYER_HP)
	{
		*(int*)param = hp_;
	}

	if (message == EventMessage::HIT_ENEMY)
	{
		//Hit(*(Vector3*)param);
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
			position_ = result + rotation_.Up()*(body_->length()*0.7f + body_->radius()*0.7f);
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
	//ジョイパッドが刺さっているか
	if (GetJoypadNum() == 0){
		float X = 0, Y = 0;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A)){
			X = -1.0f;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D)){
			X = 1.0f;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)) {
			Y = 1.0f;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)) {
			Y = -1.0f;
		}
		Move(Vector2(X,Y));
	}
	else{
		Move(GamePad::GetInstance().Stick());
	}
	//攻撃
	if (state_ != ActionPlayerState::ActionPlayerAttack)
	{
		mAttackCount = 0;
		mAttackcheck = false;
		Attack();
	}

	//回避
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) || Keyboard::GetInstance().KeyStateDown(KEYCODE::LSHIFT)) {
		change_state(ActionPlayerState::ActionPlayerAvoidance, ActionPlayerMotion::Motion::MotionPlayerAvoidance);
	}
}

void ActionPlayer::Move(Vector2 input)
{
	if (state_ == ActionPlayerState::ActionPlayerAttack || state_ == ActionPlayerState::ActionPlayerAvoidanceAttack) return;
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

	side_speed = input.x * spped;
	forward_speed = input.y * spped;

	//カメラの前方方向を前方向とする
	Vector3 ForwardVec = m_ActionCameraForward * forward_speed;
	velocity_ += ForwardVec;
	Vector3 SideVec = m_ActionCameraRight * side_speed;
	velocity_ += SideVec;

	//回避加速度
	static const int mAvoidanceSpeed = 5.0f;

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

	//進んでいる方向に向く
	Vector3 angle = m_ActionCameraForward * input.y + m_ActionCameraRight * input.x;
	angle.y = 0.0f;
	Matrix to_Target_rotate = Matrix::CreateLookAt(position_, position_ + angle.Normalize(), Vector3::Up);
	rotation_ = Matrix::Lerp(rotation_, Matrix::Invert(to_Target_rotate) * Matrix::CreateRotationY(180), 0.1f);

	position_ += velocity_ * (1.0f + DashSpped);
}

void ActionPlayer::Attack()
{
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		if (state_ == ActionPlayerState::ActionPlayerAvoidance) {
			change_state(ActionPlayerState::ActionPlayerAvoidanceAttack, ActionPlayerMotion::MotionPlayerAvoidanceAttack);
			return;
		}
		mAttackcheck = false;
		mAttackCount += 1;
		switch (mAttackCount) {
		case 1:
			change_state(ActionPlayerState::ActionPlayerAttack, ActionPlayerMotion::MotionPlayerAttack1); break;
		case 2:
			change_state(ActionPlayerState::ActionPlayerAttack, ActionPlayerMotion::MotionPlayerAttack2); break;
		case 3:
			change_state(ActionPlayerState::ActionPlayerAttack, ActionPlayerMotion::MotionPlayerAttack3); break;
		default:break;
		}
	}
}

void ActionPlayer::AttackSystem()
{
	switch (mAttackCount) {
	case 1:
		if (state_timer_ == 38.0f) AttackCollision(20, 1, Vector3(0.0f, 13.0f, 0.0f), 2.5f, 3.5f); break;
	case 2:
		if (state_timer_ == 5.0f) AttackCollision(20, 2, Vector3(0.0f, 13.0f, 0.0f), 2.5f, 3.5f); break;
	case 3:
		if (state_timer_ == 5.0f) AttackCollision(20, 3, Vector3(0.0f, 13.0f, 0.0f), 2.5f, 3.5f); break;
	default:
		break;
	}

	if (state_timer_ > mesh_.motion_end_time() - 10)
	{
		mAttackcheck = true;
		Attack();
	}
}

void ActionPlayer::AttackAvoidanceSystem()
{
	if (state_timer_ == 25.0f)AttackCollision(20, 1, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
	if (state_timer_ == 40.0f)AttackCollision(20, 2, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
}

void ActionPlayer::AttackCollision(int deadTime, int attackParam, Vector3 spot, float len, float rad)
{
	auto AttackPunch = std::make_shared<PlayerAttackCollision>(world_, Vector3{ position_ + Getpose().Forward() * 10 },
		std::make_shared<BoundingCapsule>(spot, Matrix::Identity, len, rad));
	world_->add_actor(ActorGroup::PlayerBullet, AttackPunch);
	AttackPunch->SetParam(false, deadTime, attackParam);
}

void ActionPlayer::Motion(float deltaTime)
{
	state_timer_ += 0.5f;
	if (state_ == ActionPlayerState::ActionPlayerAttack){
		AttackSystem();
	}
	else if (state_ == ActionPlayerState::ActionPlayerAvoidanceAttack) {
		AttackAvoidanceSystem();
	}

	if (state_timer_ > mesh_.motion_end_time()-5)
	{
		switch (state_){
		case ActionPlayerState::ActionPlayerAttack:
			change_state(ActionPlayerState::ActionPlayerIdel, ActionPlayerMotion::MotionPlayerIdel);break;
		case ActionPlayerState::ActionPlayerAvoidanceAttack:
			change_state(ActionPlayerState::ActionPlayerIdel, ActionPlayerMotion::MotionPlayerIdel); break;
		case ActionPlayerState::ActionPlayerAvoidance:
			change_state(ActionPlayerState::ActionPlayerIdel, ActionPlayerMotion::MotionPlayerIdel);break;
		case ActionPlayerState::ActionPlayerDamage:
			change_state(ActionPlayerState::ActionPlayerIdel, ActionPlayerMotion::MotionPlayerIdel);break;
		case ActionPlayerState::ActionPlayerDead:
			DeadCheck = true;break;
		default: break;
		};
	}
}

void ActionPlayer::draw_weapon() const
{
	//右手に持っている武器
	StaticMesh::bind(weapon_);
	StaticMesh::transform(mesh_.bone_matrix(mRightweaponPos));
	StaticMesh::draw();

	//左手に持っている武器
	StaticMesh::bind(weapon_);
	StaticMesh::transform(mesh_.bone_matrix(mLeftweaponPos));
	StaticMesh::draw();
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