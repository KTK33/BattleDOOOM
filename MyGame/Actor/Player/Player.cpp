#include "Player.h"
#include "../PlayerBall/Ball.h"
#include "../ActorGroup.h"
#include "../../Input/GamePad.h"
#include "../../Texture/Sprite.h"
#include "../../Scene/GameData/GameDataManager.h"
#include "PlayerPunchAttack.h"


Player::Player(int model, int weapon, IWorld * world, const Vector3 & position, std::weak_ptr<Actor> ui, const IBodyPtr & body) :
	Actor(world, "Player", position, body),
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
	weaponPos{ 100 },
	invinciblyCheck{ false },
	invinciblyTime{ 100 },
	AimingCheck{ false },
	AimPos{1920/2,1080/2}
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());
	hp_ = PlayerHP;
}

void Player::initialize()
{
}

void Player::update(float deltaTime)
{
	if (world_->GetPauseCheck() == false)
	{
		mesh_.update(deltaTime);
		mesh_.transform(Getpose());
		update_state(deltaTime);
		mesh_.change_motion(motion_);
		PlayerInput();
		Delay();
	}

	world_->send_message(EventMessage::PLAYER_HP, (void*)&hp_);
	world_->send_message(EventMessage::PLAYER_REMAINGUN, (void*)&SetRemainGun);
	world_->send_message(EventMessage::PLAYER_HAVEGUN, (void*)&HaveGun);

	hp_ = MathHelper::Clamp(hp_, 0, 10);

	//collision();


	if (state_ == PlayerState::State::PlayerIdleAiming ||
		state_ == PlayerState::State::PlayerStopGun)
	{
		AimingCheck = true;
	}
	else
	{
		AimingCheck = false;
	}

	if (AimingCheck)
	{
		AimPos += GamePad::GetInstance().RightStick() * 3;
	}
}

void Player::draw() const
{
	mesh_.draw();
	draw_weapon();
	body_->transform(Getpose())->draw();

	if (AimingCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::SIGHT, AimPos);
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
			change_state(PlayerState::PlayerDamage, MotionPlayerDamage);
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
		hp_ += *(int*)param;
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
}

void Player::collision()
{
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		position_ = result;
	}

	//床との接地判定
	if (floor(result)) {
		collide = true;
		position_ = result + rotation_.Up() *(body_->length()*0.5f + body_->radius());
	}
	//else
	//{
	//	collide = false;
	//	position_.y -= 0.5f;
	//}
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
	case PlayerState::State::PlayerGunPunch:	GunPunch();		 break;
	//case PlayerState::State::PlayerMove: GunMove(motion_,deltaTime); break;
	case PlayerState::State::PlayerDamage:		Damage();		break;
	case PlayerState::State::PlayerDead:		Dead();			break;
	default: break;
	};
	//state_timer_ += deltaTime;
}

void Player::change_state(PlayerState::State state, int motion)
{
	motion_ = motion;
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
				change_state(PlayerState::PlayerAimToIdle, MotionPlayerAimToIdle);
			}
		}
	}

	//リロード
	if (SetRemainGun < SetGunPoint && HaveGun > 0 &&
		GamePad::GetInstance().ButtonStateUp(PADBUTTON::NUM6) &&
		GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3) &&
		state_ != PlayerState::PlayerReload)
	{
		before_motion_ = motion_;
		before_state_ = state_;
		change_state(PlayerState::PlayerReload, MotionPlayerReload);
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM4) && state_ != PlayerState::PlayerGunPunch) {
		before_motion_ = motion_;
		before_state_ = state_;
		change_state(PlayerState::PlayerGunPunch, MotionPlayerGunPunch);
	}
}

void Player::Idle()
{
	if (GamePad::GetInstance().Stick().x != 0.0f || GamePad::GetInstance().Stick().y != 0.0f)
	{
		Move(GamePad::GetInstance().Stick().x, GamePad::GetInstance().Stick().y);

		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5)) {
			change_state(PlayerState::PlayerIdleToAim, MotionPlayerIdleToAim);
		}
	}
	else
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5)) {
			change_state(PlayerState::PlayerIdleToAim, MotionPlayerIdleToAim);
		}
		else
		{
			change_state(PlayerState::PlayerIdel, MotionPlayerIdel);
		}
	}

	float yaw_speed{ 0.0f };
	yaw_speed = GamePad::GetInstance().RightStick().x;
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), yaw_speed * 1.0f);
	rotation_.NormalizeRotationMatrix();
}

void Player::IdletoAim()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time()){
		change_state(PlayerState::PlayerIdleAiming, MotionPlayerIdleAiming);
	}
}

void Player::AimtoIdle()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time()){
		change_state(PlayerState::PlayerIdel, MotionPlayerIdel);
	}
}

void Player::IdleAiming()
{
	if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM5)){
		change_state(PlayerState::PlayerAimToIdle, MotionPlayerAimToIdle);
	}

	if (GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6)){
		change_state(PlayerState::PlayerStopGun, MotionPlayerStopGun);
		Gun(state_,motion_);
	}

	GunMove(GamePad::GetInstance().Stick().x, GamePad::GetInstance().Stick().y);

}

void Player::StopGun()
{
	Gun(state_,motion_);

	if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM5)){
		change_state(PlayerState::PlayerAimToIdle, MotionPlayerAimToIdle);
	}

	if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM6)){
		change_state(PlayerState::PlayerIdleAiming, MotionPlayerIdleAiming);
	}

	GunMove(GamePad::GetInstance().Stick().x, GamePad::GetInstance().Stick().y);
}

void Player::Reload()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		int setpoint{ 0 };
		if (HaveGun < SetGunPoint){
			setpoint = HaveGun - SetGunPoint;
		}

		HaveGun = max(HaveGun + (SetRemainGun - SetGunPoint),0);
		SetRemainGun = SetGunPoint +setpoint;

		DelayGunTime = 30;

		if (GamePad::GetInstance().ButtonStateUp(PADBUTTON::NUM5))
		{
			change_state(PlayerState::PlayerIdel, MotionPlayerIdel);
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
		auto AttackPunch = std::make_shared<PlayerPunchAttack>(world_, Vector3{ position_ + Getpose().Forward() * 4 },
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
void Player::GunMove(float X,float Y)
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
	velocity_ += rotation_.Forward() * forward_speed;
	velocity_ += rotation_.Left() * side_speed;
	position_ += velocity_ * 1.0f;

	if (X > 0.0f){
		motion_ = MotionPlayerLeftGun;
	}
	if (X < 0.0f){
		motion_ = MotionPlayerLeftGun;
	}
	if (Y > 0.0f){
		motion_ = MotionPlayerForwardGun;
	}
	if (Y < 0.0f){
		motion_ = MotionPlayerBackGun;
	}

	if (side_speed == 0.0f && forward_speed == 0.0f)
	{
		change_state(PlayerState::PlayerIdleAiming, MotionPlayerIdleAiming);
	}

}
void Player::Move(float X, float Y)
{
	//前後左右移動
	velocity_ = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };
	float yaw_speed{ 0.0f };

	side_speed = -X * 0.75f;
	forward_speed = Y * 0.75f;

	motion_ = MotionPlayerRun;

	yaw_speed = GamePad::GetInstance().RightStick().x;
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), yaw_speed * 1.0f);
	rotation_.NormalizeRotationMatrix();

	velocity_ += rotation_.Forward() * forward_speed;
	velocity_ += rotation_.Left() * side_speed;
	position_ += velocity_ * 1.0f;
}

void Player::Gun(PlayerState::State state,int motion)
{
	if (GamePad::GetInstance().Stick().y >= 0)
	{
		if (SetRemainGun > 0 && !CheckGun) {
			world_->add_actor(ActorGroup::PlayerBullet, std::make_shared<Ball>(5, world_, Vector3{ position_.x,position_.y + 10.0f,position_.z } +Getpose().Forward() * 10,AimPos));
			SetRemainGun -= 1;
			CheckGun = true;
		}
	}
}

void Player::Damage()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		change_state(PlayerState::PlayerIdel, MotionPlayerIdel);
	}
}

void Player::Dead()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time() + 100)
	{
		GameDataManager::getInstance().SetPlayerDead(true);
		die();
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
		else{
			motion_ = MotionPlayerDead;
			state_ = PlayerState::PlayerDead;
		}
	}
}

void Player::Hit(Vector3 & dir)
{
	Vector3 dir_ = Vector3::Normalize(dir);
	//アクターからプレイヤーの方向に移動
	velocity_ = Vector3::Up * 7.0f + Vector3{ dir_.x,0.f,dir_.z } *2.0f;
	//collide = true;
}
