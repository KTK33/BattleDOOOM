#include "Player.h"
#include "../PlayerBall/Ball.h"
#include "../Enemy/TestEnemy.h"
#include "../ActorGroup.h"
#include "../../Input/GamePad.h"


Player::Player(int model,int weapon,IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world,"Player",position,body),
	mesh_{model,weapon},
	weapon_{weapon},
	RemainGun{10},
	DelayGunTime{ 30 },
	state_{ PlayerState::IDLE },
	state_timer_{0.0f}
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());
	hp_ = 10;
}

void Player::initialize()
{
}

void Player::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	update_state(deltaTime);
	mesh_.change_motion(motion_);
	move(deltaTime);
	if(state_ != PlayerState::JUMP) gravity(deltaTime);
}

void Player::draw() const
{
	mesh_.draw();
	draw_weapon();
	body_->transform(Getpose())->draw();


	SetFontSize(64);
	DrawFormatString(0, 400, GetColor(255, 255, 255), "%i", RemainGun);
	DrawFormatString(0, 500, GetColor(255, 255, 255), "%i",DelayGunTime);
	SetFontSize(16);

	DrawBox(0, 50, 100 * hp_, 100, GetColor(255, 255, 255), TRUE);
}

void Player::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER, (void*)&hitdir);
}

void Player::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_ENEMY)
	{
		//die();
	}
}

void Player::collision()
{
	//�Ԃ�������
	Vector3 result;
	//�ǂƂԂ��Ă���
	if (field(result)) {
		position_ = result;
	}

	//���Ƃ̐ڒn����
	if (floor(result)) {
		position_ = result + rotation_.Up() *(body_->length()*0.5f + body_->radius());
	}

}

void Player::gravity(float deltaTime)
{
	//if (position_.y >= 0.0f)
	//{
	//	position_.y -= 9.6f * deltaTime;
	//}

	//position_.y = min(position_.y - 3, 0.0f);
}

void Player::update_state(float delta_time)
{
	//��ԑJ��
	switch (state_)
	{
	case PlayerState::State::MOVE: move(delta_time); break;
	case PlayerState::State::PUNCH:punch(delta_time); break;
	case PlayerState::State::KICK:kick(delta_time); break;
	case PlayerState::State::SWORD:sword(delta_time); break;
	case PlayerState::State::GUN:gun(delta_time); break;
	case PlayerState::State::DAMAGE:damage(delta_time); break;
	case PlayerState::State::JUMP:jump(delta_time); break;
	};
	state_timer_ += delta_time;
}

void Player::change_state(PlayerState::State state, int motion)
{
	motion_ = motion;
	state_ = state;
	state_timer_ = 0.0f;
}

void Player::move(float delta_time)
{
	if (CheckHitKey(KEY_INPUT_V) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM2))
	{
		//motion_ = MotionFire;
		change_state(PlayerState::State::PUNCH, MotionPunch);
		return;
	}
	//if (CheckHitKey(KEY_INPUT_B) ||
	//	GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM2))
	//{
	//	//motion_ = MotionFire;
	//	change_state(PlayerState::State::KICK, MotionKick);
	//	return;
	//}
	//if (CheckHitKey(KEY_INPUT_N) ||
	//	GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM2))
	//{
	//	//motion_ = MotionFire;
	//	change_state(PlayerState::State::SWORD, MotionSword);
	//	return;
	//}

	if (CheckHitKey(KEY_INPUT_R) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6))
	{
		change_state(PlayerState::State::GUN, MotionGun);
		return;
	}


	if (CheckHitKey(KEY_INPUT_F) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM3))
	{
		RemainGun = 10;
	}

	//�W�����v
	if (CheckHitKey(KEY_INPUT_U) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM1))
	{
		velocity_.y = 1.0f;
		change_state(PlayerState::State::JUMP, MotionJump);
		return;
	}
	//�������Ȃ���΃A�C�h�����
	int motion{ MotionIdel };
	DelayGunTime = 30;
	//�O�㍶�E�ړ�
	velocity_ = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };
	float yaw_speed{ 0.0f };
	//if (GamePad::GetInstance().ButtonStateDown(PADBUTTON::UP)
	//	||CheckHitKey(KEY_INPUT_W))
	//{
	//	forward_speed = WalkSpeed;
	//	motion = MotionForwardWalk;
	//}
	//else if (GamePad::GetInstance().ButtonStateDown(PADBUTTON::DOWN)
	//	|| CheckHitKey(KEY_INPUT_S))
	//{
	//	forward_speed = -WalkSpeed;
	//	motion = MotionBackarWalk;
	//}
	//else if (GamePad::GetInstance().ButtonStateDown(PADBUTTON::LEFT)
	//	|| CheckHitKey(KEY_INPUT_A))
	//{
	//	side_speed = WalkSpeed;
	//	motion = MotionLeftWalk;
	//}
	//else if (GamePad::GetInstance().ButtonStateDown(PADBUTTON::RIGHT)
	//	|| CheckHitKey(KEY_INPUT_D))
	//{
	//	side_speed = -WalkSpeed;
	//	motion = MotionRightWalk;
	//}

	side_speed = -GamePad::GetInstance().Stick().x * 0.5f;

	forward_speed = GamePad::GetInstance().Stick().y * 0.5f;


	if (side_speed != 0.0f || forward_speed != 0.0f){
		motion = MotionForwardWalk;
	}

	yaw_speed = GamePad::GetInstance().RightStick().x;

	change_state(PlayerState::State::MOVE, motion);
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), yaw_speed * delta_time);
	rotation_.NormalizeRotationMatrix();
	velocity_ += rotation_.Forward() * forward_speed;
	velocity_ += rotation_.Left() * side_speed;
	position_ += velocity_ * delta_time;
}

void Player::punch(float delta_time)
{
	if (state_timer_ >= mesh_.motion_end_time())
	{
		move(delta_time);
	}
}
void Player::kick(float delta_time)
{
	if (state_timer_ >= mesh_.motion_end_time())
	{
		move(delta_time);
	}
}
void Player::sword(float delta_time)
{
	if (state_timer_ >= mesh_.motion_end_time())
	{
		move(delta_time);
	}
}
void Player::gun(float delta_time)
{
	if (RemainGun > 0 && DelayGunTime == 30){
		world_->add_actor(ActorGroup::PlayerBullet, std::make_shared<Ball>(2, world_, Vector3{ position_.x,position_.y + 5.0f,position_.z }));
		RemainGun -= 1;
	}

	DelayGunTime--;

	if (DelayGunTime <= 0) DelayGunTime = 30;

	if (state_timer_ >= mesh_.motion_end_time())
	{
		DelayGunTime = 30;
		change_state(PlayerState::State::IDLE, MotionIdel);
	}
}


void Player::damage(float delta_time)
{
	if (state_timer_ >= mesh_.motion_end_time())
	{
		move(delta_time);
	}
}

void Player::jump(float delta_time)
{
	position_ += velocity_ * delta_time;
	velocity_.y += Gravity * delta_time;
	if (position_.y < 0.0f)
	{
		position_.y = 0.0f;
		move(delta_time);
	}
}

void Player::draw_weapon() const
{
	StaticMesh::bind(weapon_);
	StaticMesh::transform(mesh_.bone_matrix(100));//19�Ԃ�����p�̎�̃{�[��
	StaticMesh::draw();
}
