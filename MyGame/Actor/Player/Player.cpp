#include "Player.h"
#include "../PlayerBall/Ball.h"
#include "../ActorGroup.h"
#include "../../Input/GamePad.h"
#include "../../Texture/Sprite.h"
#include "../../Scene/GameData/GameDataManager.h"
#include "PlayerPunchAttack.h"
#include "PlayerItemBox.h"
#include "PlayerMotionNum.h"


Player::Player(int model, int weapon, IWorld * world, const Vector3 & position, std::weak_ptr<Actor> ui, const IBodyPtr & body) :
	Actor(world, "Player", position, body),
	Initbody{body},
	m_ui{ ui },
	mesh_{ model,weapon },
	weapon_{ weapon },
	SetRemainGun{ SetGunPoint },
	DelayGunTime{ 20 },
	HaveGun{ 10 },
	CheckGun{ false },
	state_{ PlayerState::PlayerIdel },
	before_state_{ PlayerState::NONE },
	state_timer_{ 0.0f },
	weaponPos{ 103 },
	invinciblyCheck{ false },
	invinciblyTime{ 100 },
	AimPos{ position_.x + rotation_.Forward().x * 10 + rotation_.Right().x * 5, position_.y + 15, position_.z + rotation_.Forward().z * 10 + rotation_.Right().z * 5 },
	RecoverItemCount{0},
	AttackItemCount{0},
	alreadyItem{false},
	DeadCheck{false}
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());
	hp_ = PlayerHP;

	InitAimPos = AimPos;
}

void Player::initialize()
{
}

void Player::update(float deltaTime)
{
	if (world_->GetPauseCheck() == false)
	{
		if (!DeadCheck)
		{
			mesh_.update(deltaTime);
			mesh_.transform(Getpose());
			update_state(deltaTime);
			mesh_.change_motion(motion_);
			PlayerInput();
			Delay();
		}
	}

	world_->send_message(EventMessage::PLAYER_HP, (void*)&hp_);
	world_->send_message(EventMessage::PLAYER_REMAINGUN, (void*)&SetRemainGun);
	world_->send_message(EventMessage::PLAYER_HAVEGUN, (void*)&HaveGun);

	hp_ = MathHelper::Clamp(hp_, 0, 10);

	//velocity_ = Vector3::Zero;
	velocity_ += Vector3::Up * -gravity;
	position_ += velocity_;
	velocity_ *= 0.8f;
	if (velocity_.Length() < 0.01f) {
		velocity_ = 0.0f;
	}

	collision();
	if (floorcollide) gravity = 0.0f;

	if (state_ == PlayerState::State::PlayerIdleAiming ||
		state_ == PlayerState::State::PlayerStopGun)
	{
		GameDataManager::getInstance().SetSightCheck(true);
	}
	else
	{
		GameDataManager::getInstance().SetSightCheck(false);
		AimPos = Vector3::Lerp(AimPos, InitAimPos, 0.1f);
	}

	//if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
	//{
	//	weaponPos = weaponPos + 1;
	//}
	//if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2))
	//{
	//	weaponPos = weaponPos - 1;
	//}

	if (GetJoypadPOVState(DX_INPUT_PAD1, 0) == 9000 && !alreadyItem && state_ == PlayerState::State::PlayerIdel && GameDataManager::getInstance().GetPlayerDead() == false)
	{
		if (world_->find_actor(ActorGroup::ItemBoxUI, "PlayerBox") == NULL)
		{
			world_->add_actor(ActorGroup::ItemBoxUI, new_actor<PlayerItemBox>(world_, RecoverItemCount, AttackItemCount, weak_from_this()));
		}
		alreadyItem = true;
	}
	else{
		alreadyItem = false;
	}

	prevPosition_ = position_;
}

void Player::draw() const
{
	mesh_.draw();
	draw_weapon();
	body_->transform(Getpose())->draw();

	//DrawFormatString(500, 500, GetColor(255, 255, 255), "%f", AimPosMove.x);
	//DrawFormatString(700, 500, GetColor(255, 255, 255), "%f", AimPosMove.y);

	//DrawLine3D(Vector3{ position_.x,position_.y + 15.0f,position_.z } +rotation_.Forward() * 10, AimPos, GetColor(255, 255, 255));

	//DrawFormatString(700, 900, GetColor(255, 255, 255), "%f", position_.x);
	//DrawFormatString(700, 950, GetColor(255, 255, 255), "%f", position_.y);
	//DrawFormatString(700, 1000, GetColor(255, 255, 255), "%f", position_.z);

	DrawFormatString(700, 900, GetColor(255, 255, 255), "%f", GamePad::GetInstance().Stick().x);
	DrawFormatString(700, 950, GetColor(255, 255, 255), "%f", GamePad::GetInstance().Stick().y);



	if (collide)
	{
		DrawFormatString(600, 900, GetColor(255, 255, 255), "HIT");
	}
	if (floorcollide)
	{
		DrawFormatString(600, 950, GetColor(255, 255, 255), "FloorHIT");
	}

	if (GameDataManager::getInstance().GetSightCheck() == true)
	{
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SIGHT, Vector2(ConvWorldPosToScreenPos(AimPos).x, ConvWorldPosToScreenPos(AimPos).y));
	}

}

void Player::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER, (void*)&hitdir);
}

void Player::receiveMessage(EventMessage message, void * param)
{
	if (!invinciblyCheck)
	{
		if (message == EventMessage::HIT_ENEMY_BULLET)
		{
			hp_ = hp_ - *(int*)param;
			change_state(PlayerState::PlayerDamage, PlayerMotion::Motion::MotionPlayerDamage);
			invinciblyCheck = true;
		}
	}

	if (message == EventMessage::GET_BULLET)
	{
		HaveGun += *(int*)param;
		m_ui.lock()->receiveMessage(EventMessage::GET_BULLET, nullptr);
	}

	if (message == EventMessage::PLAYER_HP)
	{
		*(int*)param = hp_;
	}
	if (message == EventMessage::GET_HPRECOVER)
	{
		//hp_ += *(int*)param;
		RecoverItemCount = RecoverItemCount + 1;
		m_ui.lock()->receiveMessage(EventMessage::GET_HPRECOVER, nullptr);
	}
	if (message == EventMessage::PLAYER_REMAINGUN)
	{
		*(int*)param = SetRemainGun;
	}
	if (message == EventMessage::PLAYER_HAVEGUN)
	{
		*(int*)param = HaveGun;
	}

	if (message == EventMessage::HIT_ENEMY)
	{
		Hit(*(Vector3*)param);
	}

	if (message == EventMessage::SIGHT_POSITION)
	{
		AimPos = *(Vector3*)param;
	}
	if (message == EventMessage::SIGHT_ROTATION)
	{
		float rote = *(float*)param;
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), *(float*)param);
		rotation_.NormalizeRotationMatrix();
	}
	if (message == EventMessage::HP_RECOVER)
	{
		hp_ += *(int*)param;
		RecoverItemCount = RecoverItemCount - 1;
	}
}

void Player::collision()
{
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		position_.x = result.x;
		position_.z = result.z;
		collide = true;
	}
	else
	{
		collide = false;
	}

	//床との接地判定
	if (floor(result)) {
		if (state_ != PlayerState::State::PlayerJump)
		{
			floorcollide = true;
			position_ = result+rotation_.Up()*(body_->length()*0.5f + body_->radius()*0.5f);
		}
	}
	else{
		floorcollide = false;
	}
}

void Player::update_state(float deltaTime)
{
	//状態遷移
	switch (state_)
	{
	case PlayerState::State::PlayerIdel:		Idle();			break;
	case PlayerState::State::PlayerIdleToAim:	IdletoAim();	break;
	case PlayerState::State::PlayerAimToIdle:	AimtoIdle();	break;
	case PlayerState::State::PlayerIdleAiming:	IdleAiming();	break;
	case PlayerState::State::PlayerStopGun:		StopGun();		break;
	case PlayerState::State::PlayerReload:		Reload();		break;
	case PlayerState::State::PlayerGunPunch:	GunPunch();	    break;
	case PlayerState::State::PlayerJump:		Jump();			break;
	case PlayerState::State::PlayerThohatu:	    Tyohatu();	    break;
	case PlayerState::State::PlayerDamage:		Damage();		break;
	case PlayerState::State::PlayerDead:		Dead();			break;
	default: break;
	};
	//state_timer_ += deltaTime;
}

void Player::change_state(PlayerState::State state, int motion)
{
	before_motion_ = motion_;
	motion_ = motion;
	before_state_ = state_;
	state_ = state;
	state_timer_ = 0.0f;
}

void Player::PlayerInput()
{
	if (state_ != PlayerState::PlayerIdel)
	{
		if (state_ != PlayerState::PlayerReload)
		{
			if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM5)) {
				change_state(PlayerState::PlayerAimToIdle, PlayerMotion::Motion::MotionPlayerAimToIdle);
			}
		}
	}

	//リロード
	if (SetRemainGun < SetGunPoint && HaveGun > 0 &&
		GamePad::GetInstance().ButtonStateUp(PADBUTTON::NUM6) &&
		GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3) &&
		state_ != PlayerState::PlayerReload)
	{
		change_state(PlayerState::PlayerReload, PlayerMotion::Motion::MotionPlayerReload);
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM4) && state_ != PlayerState::PlayerGunPunch) {
		change_state(PlayerState::PlayerGunPunch, PlayerMotion::Motion::MotionPlayerGunPunch);
	}
}

void Player::Idle()
{
	if (GamePad::GetInstance().Stick().x != 0.0f || GamePad::GetInstance().Stick().y != 0.0f)
	{
		Move(GamePad::GetInstance().Stick().x, GamePad::GetInstance().Stick().y);

		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5)) {
			change_state(PlayerState::PlayerIdleToAim, PlayerMotion::Motion::MotionPlayerIdleToAim);
		}
	}
	else
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5)) {
			change_state(PlayerState::PlayerIdleToAim, PlayerMotion::Motion::MotionPlayerIdleToAim);
		}
		else
		{
			change_state(PlayerState::PlayerIdel, PlayerMotion::Motion::MotionPlayerIdel);
		}
	}

	float yaw_speed{ 0.0f };
	yaw_speed = GamePad::GetInstance().RightStick().x;
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), yaw_speed * 1.0f);
	rotation_.NormalizeRotationMatrix();

	if (GetJoypadPOVState(DX_INPUT_PAD1, 0) == 18000)
	{
		change_state(PlayerState::PlayerThohatu, PlayerMotion::Motion::MotionPlayerTyohatu);
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
	{
		JumpChacker(state_);
	}
}

void Player::IdletoAim()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time()) {
		change_state(PlayerState::PlayerIdleAiming, PlayerMotion::Motion::MotionPlayerIdleAiming);
	}
}

void Player::AimtoIdle()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time()) {
		change_state(PlayerState::PlayerIdel, PlayerMotion::Motion::MotionPlayerIdel);
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5))
	{
		change_state(PlayerState::PlayerIdleAiming, PlayerMotion::Motion::MotionPlayerIdleAiming);
	}
}

void Player::IdleAiming()
{
	if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM5)) {
		change_state(PlayerState::PlayerAimToIdle, PlayerMotion::Motion::MotionPlayerAimToIdle);
	}

	if (GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6)) {
		change_state(PlayerState::PlayerStopGun, PlayerMotion::Motion::MotionPlayerStopGun);
		Gun(state_, motion_);
	}

	GunMove(GamePad::GetInstance().Stick().x, GamePad::GetInstance().Stick().y);

}

void Player::StopGun()
{
	Gun(state_, motion_);

	if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM5)) {
		change_state(PlayerState::PlayerAimToIdle, PlayerMotion::Motion::MotionPlayerAimToIdle);
	}

	if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM6)) {
		change_state(PlayerState::PlayerIdleAiming, PlayerMotion::Motion::MotionPlayerIdleAiming);
	}

	GunMove(GamePad::GetInstance().Stick().x, GamePad::GetInstance().Stick().y);
}

void Player::Reload()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		int setpoint = 0;
		if (HaveGun < SetGunPoint) {
			if (HaveGun + SetRemainGun < SetGunPoint)
			{
				setpoint = SetRemainGun;
			}
			else {
				setpoint = SetGunPoint - SetRemainGun;
			}
		}
		else{
			setpoint = SetGunPoint - SetRemainGun;
		}
		HaveGun -= setpoint;
		SetRemainGun += setpoint;

		DelayGunTime = 30;

		if (GamePad::GetInstance().ButtonStateUp(PADBUTTON::NUM5))
		{
			change_state(PlayerState::PlayerIdel, PlayerMotion::Motion::MotionPlayerIdel);
		}
		else
		{
			change_state(before_state_, before_motion_);
		}
	}


}
void Player::GunPunch()
{
	state_timer_ += 1.0f;
	if (state_timer_ == 60)
	{
		auto AttackPunch = std::make_shared<PlayerPunchAttack>(world_, Vector3{ position_ + Getpose().Forward() * 6},
			std::make_shared<BoundingCapsule>(Vector3{ 0.0f,13.0f,0.0f }, Matrix::Identity, 1.5f, 2.5f));
		world_->add_actor(ActorGroup::PlayerBullet, AttackPunch);
		AttackPunch->SetdeadTime(20);
		AttackPunch->SetAttackParam(1);

	}
	if (state_timer_ >= mesh_.motion_end_time())
	{
		change_state(before_state_, before_motion_);
	}
}
void Player::GunMove(float X, float Y)
{
	//前後左右移動
	velocity_ = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };
	float yaw_speed{ 0.0f };

	side_speed = -X * 0.25f;
	forward_speed = Y * 0.25f;

	//yaw_speed = GamePad::GetInstance().RightStick().x;

	//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), yaw_speed * 1.0f);
	//rotation_.NormalizeRotationMatrix();

	//yaw_speed = GamePad::GetInstance().RightStick().x * (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
	//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), yaw_speed * 1.0f);
	//rotation_.NormalizeRotationMatrix();

	velocity_ += rotation_.Forward() * forward_speed;
	velocity_ += rotation_.Left() * side_speed;
	position_ += velocity_ * 1.0f;

	if (X > 0.0f) {
		motion_ = PlayerMotion::Motion::MotionPlayerLeftGun;
	}
	if (X < 0.0f) {
		motion_ = PlayerMotion::Motion::MotionPlayerLeftGun;
	}
	if (Y > 0.0f) {
		motion_ = PlayerMotion::Motion::MotionPlayerForwardGun;
	}
	if (Y < 0.0f) {
		motion_ = PlayerMotion::Motion::MotionPlayerBackGun;
	}

	if (side_speed == 0.0f && forward_speed == 0.0f)
	{
		change_state(PlayerState::PlayerIdleAiming, PlayerMotion::Motion::MotionPlayerIdleAiming);
	}

}
void Player::Move(float X, float Y)
{
	//前後左右移動
	velocity_ = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };
	float yaw_speed{ 0.0f };

	side_speed = -X * 0.5f;
	forward_speed = Y * 0.5f;

	if (MathHelper::Abs(X) >= 0.75f)
	{
		motion_ = PlayerMotion::Motion::MotionPlayerRun;
	}
	else if(MathHelper::Abs(Y) >= 0.75f)
	{
		motion_ = PlayerMotion::Motion::MotionPlayerRun;
	}
	else if (MathHelper::Abs(X) < 0.75f)
	{
		motion_ = PlayerMotion::Motion::MotionPlayerWalk;
	}
	else if (MathHelper::Abs(Y) < 0.75f)
	{
		motion_ = PlayerMotion::Motion::MotionPlayerWalk;
	}

	//yaw_speed = GamePad::GetInstance().RightStick().x;
	//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), yaw_speed * 1.0f);
	//rotation_.NormalizeRotationMatrix();


	velocity_ += rotation_.Forward() * forward_speed;
	velocity_ += rotation_.Left() * side_speed;
	position_ += velocity_ * 1.0f;

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
	{
		JumpChacker(state_);
	}

	prevPosition_ = position_;
}

void Player::Gun(PlayerState::State state, int motion)
{
	if (GamePad::GetInstance().Stick().y >= 0)
	{
		if (SetRemainGun > 0 && !CheckGun) {
			world_->add_actor(ActorGroup::PlayerBullet, std::make_shared<Ball>(world_, Vector3{ position_.x,position_.y + 13.0f,position_.z } +rotation_.Forward() * 4 + rotation_.Right() * 3, AimPos));
			SetRemainGun -= 1;
			CheckGun = true;
		}
	}
}

void Player::JumpChacker(PlayerState::State state)
{
	switch (state)
	{
	case PlayerState::PlayerIdel:
		change_state(PlayerState::PlayerJump, PlayerMotion::Motion::MotionPlayerJump);
		break;
	case PlayerState::PlayerRun:
		change_state(PlayerState::PlayerJump, PlayerMotion::Motion::MotionPlayerRunJump);
		break;
	}
}

void Player::Jump()
{
	//前後左右移動
	velocity_ = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };
	float yaw_speed{ 0.0f };
	side_speed = -GamePad::GetInstance().Stick().x * 0.25f;
	forward_speed = GamePad::GetInstance().Stick().y * 0.25f;

	velocity_ += rotation_.Forward() * forward_speed;
	velocity_ += rotation_.Left() * side_speed;
	position_ += velocity_ * 1.0f;

	state_timer_ += 1.0f;

	if (state_timer_ >= mesh_.motion_end_time() *0.7f){
		body_ = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,15.0f,0.0f }, Matrix::Identity, 6.0f, 4.0f);
	}
	if (state_timer_ >= mesh_.motion_end_time() +15) {
		body_ = Initbody;
	}
	if (state_timer_ >= mesh_.motion_end_time()+30)
	{
		gravity = 9.8f*0.1f;
		change_state(PlayerState::PlayerIdel, before_motion_);
	}
}

void Player::Damage()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		change_state(PlayerState::PlayerIdel, PlayerMotion::Motion::MotionPlayerIdel);
	}
}

void Player::Dead()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time() + 100)
	{
		DeadCheck = true;
		//die();
	}
}

void Player::Tyohatu()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time() + 50)
	{
		change_state(PlayerState::PlayerIdel, PlayerMotion::Motion::MotionPlayerIdel);
	}
}

void Player::draw_weapon() const
{
	StaticMesh::bind(weapon_);
	StaticMesh::transform(mesh_.bone_matrix(weaponPos));
	StaticMesh::draw();
}

void Player::Delay()
{
	if (CheckGun) {
		DelayGunTime--;
		if (DelayGunTime <= 0)
		{
			CheckGun = false;
			DelayGunTime = 20;
		}
	}

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
			motion_ = PlayerMotion::Motion::MotionPlayerDead;
			state_ = PlayerState::PlayerDead;
			GameDataManager::getInstance().SetPlayerDead(true);
		}
	}
}

void Player::Hit(Vector3 & dir)
{
	Vector3 dir_ = Vector3::Normalize(dir);
	//アクターからプレイヤーの方向に移動
	//velocity_ = Vector3::Up * 7.0f + Vector3{ dir_.x,0.f,dir_.z } *2.0f;
	velocity_.x = Vector3::Up.x * 7.0f + dir_.x*2.0f;
	velocity_.z = Vector3::Up.z * 7.0f + dir_.z*2.0f;
	//collide = true;
}