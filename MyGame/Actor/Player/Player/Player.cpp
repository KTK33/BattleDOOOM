#include "Player.h"
#include "../Actor/PlayerBullet/PlayerBullet.h"
#include "../../ActorGroup.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
#include "../Texture/Sprite.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Actor/PlayerAttackCollision/PlayerAttackCollision.h"
#include "../PlayerItemBox/PlayerItemBox.h"
#include "../PlayerMotionNum.h"

Player::Player(int model, int weapon, IWorld * world, const Vector3 & position, std::weak_ptr<Actor> ui, const IBodyPtr & body) :
	Actor(world, "Player", position, body),
	Initbody{ body },
	m_ui{ ui },
	mesh_{ model,weapon },
	weapon_{ weapon },
	SetRemainGun{ SetGunPoint },
	DelayGunTime{ 0 },
	HaveGun{ 10 },
	state_{ PlayerState::PlayerIdel },
	before_state_{ PlayerState::NONE },
	state_timer_{ 0.0f },
	weaponPos{ 103 },
	invinciblyCheck{ false },
	invinciblyTime{ 100 },
	AimPos{ position_.x + rotation_.Forward().x * 10 + rotation_.Right().x * 5, position_.y + 15, position_.z + rotation_.Forward().z * 10 + rotation_.Right().z * 5 },
	RecoverItemCount{ 1 },
	AttackItemCount{ 1 },
	alreadyItem{ false },
	DeadCheck{ false },
	GunPossible{ false },
	AttackUpCheck{false},
	AttackUpTime{600}
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());
	hp_ = PlayerHP;

	AttackParam = 1;

	ActorSystem::TransparenceInit();

	InitAimPos = AimPos;
}

void Player::initialize()
{
}

void Player::update(float deltaTime)
{
	if (world_->GetPauseCheck() == false 
		&& GameDataManager::getInstance().GetDeadBossEnemy() == false)	{
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

	world_->send_message(EventMessage::PLAYER_HP, reinterpret_cast<void*>(&hp_));
	world_->send_message(EventMessage::PLAYER_REMAINGUN, reinterpret_cast<void*>(&SetRemainGun));
	world_->send_message(EventMessage::PLAYER_HAVEGUN, reinterpret_cast<void*>(&HaveGun));

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
	
	if(GunPossible)
	{
		GameDataManager::getInstance().SetSightCheck(true);
	}
	else
	{
		GameDataManager::getInstance().SetSightCheck(false);
		AimPos = Vector3::Lerp(AimPos, InitAimPos, 0.1f);
	}


	if (GetJoypadPOVState(DX_INPUT_PAD1, 0) == 9000 || Keyboard::GetInstance().KeyStateDown(KEYCODE::F))
	{
		if (!alreadyItem && state_ == PlayerState::State::PlayerIdel && GameDataManager::getInstance().GetPlayerDead() == false)
		{
			if (world_->find_actor(ActorGroup::ItemBoxUI, "PlayerBox") == NULL)
			{
				world_->add_actor(ActorGroup::ItemBoxUI, new_actor<PlayerItemBox>(world_, RecoverItemCount, AttackItemCount, weak_from_this()));
			}
			alreadyItem = true;
		}
	}
	else{
		alreadyItem = false;
	}

	if (invinciblyCheck) {
		ActorTransparence();
	}
	else {
		TransparenceInit();
	}

	if (AttackUpCheck){
		AttackParam = 2;
		AttackUpTime = max(AttackUpTime - 1, 0);
		if (AttackUpTime == 0)
		{
			AttackUpTime = 600;
			AttackUpCheck = false;	
			int DamageParam = 1;
			world_->send_message(EventMessage::DAMAGEPARAM, reinterpret_cast<void*>(&DamageParam));
		}
	}
	else{
		AttackParam = 1;
	}

	prevPosition_ = position_;
}

void Player::draw() const
{
	mesh_.draw();
	draw_weapon();

	if (GameDataManager::getInstance().GetSightCheck() == true)
	{
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SIGHT, Vector2(ConvWorldPosToScreenPos(AimPos).x, ConvWorldPosToScreenPos(AimPos).y));
	}

	if (SetRemainGun == 0)
	{
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::BULLET_EMPTY, Vector2(960, 800));
	}
}

void Player::onCollide(Actor & other)
{
	const Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER, (void*)&hitdir);
}

void Player::receiveMessage(EventMessage message, void * param)
{
	if (!invinciblyCheck)
	{
		if (message == EventMessage::HIT_ENEMY_BULLET)
		{
			hp_ = hp_ - *static_cast<int*>(param);
			change_state(PlayerState::PlayerDamage, PlayerMotion::Motion::MotionPlayerDamage);
			invinciblyCheck = true;
		}
	}

	if (message == EventMessage::GET_BULLET)
	{
		HaveGun += *static_cast<int*>(param);
		m_ui.lock()->receiveMessage(EventMessage::GET_BULLET, nullptr);
	}

	if (message == EventMessage::PLAYER_HP)
	{
		*static_cast<int*>(param) = hp_;
	}
	if (message == EventMessage::GET_HPRECOVER)
	{
		//hp_ += *(int*)param;
		RecoverItemCount = RecoverItemCount + 1;
		m_ui.lock()->receiveMessage(EventMessage::GET_HPRECOVER, nullptr);
	}
	if (message == EventMessage::PLAYER_REMAINGUN)
	{
		*static_cast<int*>(param) = SetRemainGun;
	}
	if (message == EventMessage::PLAYER_HAVEGUN)
	{
		*static_cast<int*>(param) = HaveGun;
	}

	if (message == EventMessage::HIT_ENEMY)
	{
		Hit(*static_cast<Vector3*>(param));
	}

	if (message == EventMessage::SIGHT_POSITION)
	{
		AimPos = *static_cast<Vector3*>(param);
	}
	if (message == EventMessage::SIGHT_ROTATION)
	{
		float rote = *(float*)param;
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), *static_cast<float*>(param));
		rotation_.NormalizeRotationMatrix();
	}
	if (message == EventMessage::HP_RECOVER)
	{
		hp_ += *static_cast<int*>(param);
		RecoverItemCount = RecoverItemCount - 1;
	}
	if (message == EventMessage::ATTACK_UP)
	{
		AttackUpCheck = *static_cast<bool*>(param);
		m_ui.lock()->receiveMessage(EventMessage::ATTACK_UP, reinterpret_cast<bool*>(param));
		AttackItemCount = AttackItemCount - 1;
	}
}

void Player::collision()
{
	//�Ԃ�������
	Vector3 result;
	//�ǂƂԂ��Ă���
	if (field(result)) {
		position_.x = result.x;
		position_.z = result.z;

		Stagecollide = true;
	}
	else
	{
		Stagecollide = false;
	}

	//���Ƃ̐ڒn����
	if (floor(result)) {
		if (state_ != PlayerState::State::PlayerJump)
		{
			Floorcollide = true;
			position_ = result+rotation_.Up()*(body_->length()*0.5f + body_->radius()*0.5f);
		}
	}
	else{
		Floorcollide = false;
	}
}

void Player::update_state(float deltaTime)
{
	//��ԑJ��
	switch (state_)
	{
	case PlayerState::State::PlayerIdel:		Idle();			break;
	case PlayerState::State::PlayerIdleToAim:	IdletoAim();	break;
	case PlayerState::State::PlayerAimToIdle:	AimtoIdle();	break;
	case PlayerState::State::PlayerIdleAiming:	IdleAiming();	break;
	case PlayerState::State::PlayerGun:			PlayerGunFire();break;
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
			if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM5)||Keyboard::GetInstance().KeyTriggerUp(KEYCODE::LSHIFT)) {
				change_state(PlayerState::PlayerAimToIdle, PlayerMotion::Motion::MotionPlayerAimToIdle);
			}
		}
	}

	//�����[�h
	if (SetRemainGun < SetGunPoint && HaveGun > 0)
	{
		if (state_ != PlayerState::PlayerReload)
{
			if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3))
			{
				if (GamePad::GetInstance().ButtonStateUp(PADBUTTON::NUM6))
				{
					change_state(PlayerState::PlayerReload, PlayerMotion::Motion::MotionPlayerReload);
				}
			}
			else if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::R))
			{
				if (Keyboard::GetInstance().KeyStateUp(KEYCODE::SPACE))
				{
					change_state(PlayerState::PlayerReload, PlayerMotion::Motion::MotionPlayerReload);
				}
			}
		}
	}

	if ((GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM4) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Q)) && state_ != PlayerState::PlayerGunPunch) {
		change_state(PlayerState::PlayerGunPunch, PlayerMotion::Motion::MotionPlayerGunPunch);
	}
}

void Player::Idle()
{
	GunPossible = false;
	if (GamePad::GetInstance().Stick().x != 0.0f || GamePad::GetInstance().Stick().y != 0.0f || 
		Keyboard::GetInstance().KeyStateDown(KEYCODE::D) || Keyboard::GetInstance().KeyStateDown(KEYCODE::A)||
		Keyboard::GetInstance().KeyStateDown(KEYCODE::W) || Keyboard::GetInstance().KeyStateDown(KEYCODE::S))
	{
		Move(GamePad::GetInstance().Stick().x, GamePad::GetInstance().Stick().y);

		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5)|| Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LSHIFT)) {
			change_state(PlayerState::PlayerIdleToAim, PlayerMotion::Motion::MotionPlayerIdleToAim);
		}
	}
	else
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LSHIFT)) {
			change_state(PlayerState::PlayerIdleToAim, PlayerMotion::Motion::MotionPlayerIdleToAim);
		}
		else
		{
			change_state(PlayerState::PlayerIdel, PlayerMotion::Motion::MotionPlayerIdel);
		}
	}

	float yaw_speed{ 0.0f };
	if( Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
	{
		yaw_speed = 1.0f;
	}
	else if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
	{
		yaw_speed = -1.0f;
	}
	else
	{
		yaw_speed = GamePad::GetInstance().RightStick().x;
	}
			
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), yaw_speed * 1.0f);
	rotation_.NormalizeRotationMatrix();

	if (GetJoypadPOVState(DX_INPUT_PAD1, 0) == 18000 || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Y))
	{
		change_state(PlayerState::PlayerThohatu, PlayerMotion::Motion::MotionPlayerTyohatu);
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LCTRL))
	{
		JumpChacker(state_);
	}
}

void Player::IdletoAim()
{
	GunPossible = false;
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time()) {
		change_state(PlayerState::PlayerIdleAiming, PlayerMotion::Motion::MotionPlayerIdleAiming);
	}
}

void Player::AimtoIdle()
{
	GunPossible = false;
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time()) {
		change_state(PlayerState::PlayerIdel, PlayerMotion::Motion::MotionPlayerIdel);
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LSHIFT))
	{
		change_state(PlayerState::PlayerIdleAiming, PlayerMotion::Motion::MotionPlayerIdleAiming);
	}
}

void Player::IdleAiming()
{
	if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM5) || Keyboard::GetInstance().KeyTriggerUp(KEYCODE::LSHIFT)) {
		change_state(PlayerState::PlayerAimToIdle, PlayerMotion::Motion::MotionPlayerAimToIdle);
	}

	if (SetRemainGun > 0 && motion_ != PlayerMotion::Motion::MotionPlayerBackGun)
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM6) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)) {
			change_state(PlayerState::PlayerGun, PlayerMotion::Motion::MotionPlayerStopGun);
		}
	}

	GunMove(GamePad::GetInstance().Stick().x, GamePad::GetInstance().Stick().y);

}
void Player::Reload()
{
	GunPossible = false;
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		int setpoint = 0;
		if (HaveGun < SetGunPoint) {
			if (HaveGun + SetRemainGun < SetGunPoint)
			{
				setpoint = HaveGun;
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

		if (GamePad::GetInstance().ButtonStateUp(PADBUTTON::NUM5) || Keyboard::GetInstance().KeyStateUp(KEYCODE::LSHIFT))
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
		auto AttackPunch = std::make_shared<PlayerAttackCollision>(world_, Vector3{ position_ + Getpose().Forward() * 6},
			std::make_shared<BoundingCapsule>(Vector3{ 0.0f,13.0f,0.0f }, Matrix::Identity, 1.5f, 2.5f));
		world_->add_actor(ActorGroup::PlayerBullet, AttackPunch);
		AttackPunch->SetParam(false, 20, 1);

	}
	if (state_timer_ >= mesh_.motion_end_time())
	{
		change_state(before_state_, before_motion_);
	}
}
void Player::GunMove(float X, float Y)
{
	//�O�㍶�E�ړ�
	velocity_ = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
	{
		X = -0.5f;
	}
	else if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
	{
		X = 0.75f;
	}
	else if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)){
		Y = 0.75f;

	}
	else if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)){
		Y = -0.75f;
	}

	side_speed = -X * 0.25f;
	forward_speed = Y * 0.25f;

	velocity_ += rotation_.Forward() * forward_speed;
	velocity_ += rotation_.Left() * side_speed;
	position_ += velocity_ * 1.0f;

	if (X > 0.0f) {
		motion_ = PlayerMotion::Motion::MotionPlayerLeftGun;
		GunPossible = true;
	}
	if (X < 0.0f) {
		motion_ = PlayerMotion::Motion::MotionPlayerLeftGun;
		GunPossible = true;
	}
	if (Y > 0.0f) {
		motion_ = PlayerMotion::Motion::MotionPlayerForwardGun;
		GunPossible = true;
	}
	if (Y < 0.0f) {
		motion_ = PlayerMotion::Motion::MotionPlayerBackGun;
		GunPossible = false;
	}

	if (state_ != PlayerState::State::PlayerGun)
	{
		if (side_speed == 0.0f && forward_speed == 0.0f)
		{
			GunPossible = true;
			change_state(PlayerState::PlayerIdleAiming, PlayerMotion::Motion::MotionPlayerIdleAiming);
		}
		else {
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::WALKSTEP_SE);
		}
	}
}
void Player::Move(float X, float Y)
{
	//�O�㍶�E�ړ�
	velocity_ = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
	{
		X = -1.0f;
	}
	else if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
	{
		X = 1.0f;
	}
	else if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)) {
		Y = 1.0f;

	}
	else if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)) {
		Y = -1.0f;
	}

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

	velocity_ += rotation_.Forward() * forward_speed;
	velocity_ += rotation_.Left() * side_speed;
	position_ += velocity_ * 1.0f;

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LCTRL))
	{
		JumpChacker(state_);
	}

	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::WALKSTEP_SE);

	prevPosition_ = position_;
}

void Player::Gun()
{
	world_->add_actor(ActorGroup::PlayerBullet, std::make_shared<PlayerBullet>(world_, Vector3{ position_.x,position_.y + 13.0f,position_.z } +rotation_.Forward() * 4 + rotation_.Right() * 3, AimPos,AttackParam));
	SetRemainGun = SetRemainGun - 1;
}

void Player::PlayerGunFire()
{
	if (state_timer_ == 5)Gun();
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		change_state(before_state_, before_motion_);
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
	//�O�㍶�E�ړ�
	velocity_ = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };
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
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::TYOHATU_SE);
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time() + 50)
	{
		Sound::GetInstance().StopSE(SE_ID::TYOHATU_SE);
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
	const Vector3 dir_ = Vector3::Normalize(dir);
	//�A�N�^�[����v���C���[�̕����Ɉړ�
	//velocity_ = Vector3::Up * 7.0f + Vector3{ dir_.x,0.f,dir_.z } *2.0f;
	//velocity_.x = Vector3::Up.x * 7.0f + dir_.x*2.0f;
	//velocity_.z = Vector3::Up.z * 7.0f + dir_.z*2.0f;
	//collide = true;
}