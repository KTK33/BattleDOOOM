#include "Player.h"
#include "../PlayerBall/Ball.h"
#include "../TestEnemy.h"
#include "../ActorGroup.h"

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
}

void Player::draw() const
{
	mesh_.draw();
	draw_weapon();
	body_->transform(Getpose())->draw();


	DrawFormatString(0, 400, GetColor(255, 255, 255), "%i", RemainGun);
	DrawFormatString(0, 420, GetColor(255, 255, 255), "%i",DelayGunTime);

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

void Player::update_state(float delta_time)
{
	//状態遷移
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
	if (CheckHitKey(KEY_INPUT_Q) ||
		GamePad::state(GamePad::B))
	{
		//motion_ = MotionFire;
		change_state(PlayerState::State::PUNCH, MotionPunch);
		return;
	}
	if (CheckHitKey(KEY_INPUT_W) ||
		GamePad::state(GamePad::X))
	{
		//motion_ = MotionFire;
		change_state(PlayerState::State::KICK, MotionKick);
		return;
	}
	if (CheckHitKey(KEY_INPUT_E) ||
		GamePad::state(GamePad::Y))
	{
		//motion_ = MotionFire;
		change_state(PlayerState::State::SWORD, MotionSword);
		return;
	}

	if (CheckHitKey(KEY_INPUT_R) ||
		GamePad::state(GamePad::RightTrigger)) {
		change_state(PlayerState::State::GUN, MotionGun);
		return;
	}


	if (CheckHitKey(KEY_INPUT_F) ||
		GamePad::state(GamePad::RightTrigger))
	{
		RemainGun = 10;
	}

	//ジャンプ
	if (CheckHitKey(KEY_INPUT_U) ||
		GamePad::trigger(GamePad::A))
	{
		velocity_.y = 1.0f;
		change_state(PlayerState::State::JUMP, MotionJump);
		return;
	}
	//何もしなければアイドル状態
	int motion{ MotionIdel };
	DelayGunTime = 30;
	//前後左右移動
	velocity_ = Vector3::Zero;
	float forward_speed{ 0.0f };
	float side_speed{ 0 };
	float yaw_speed{ 0.0f };
	if (GamePad::state(GamePad::Up))
	{
		forward_speed = WalkSpeed;
		motion = MotionForwardWalk;
	}
	else if (GamePad::state(GamePad::Down))
	{
		forward_speed = -WalkSpeed;
		motion = MotionBackarWalk;
	}
	else if (GamePad::state(GamePad::Left))
	{
		side_speed = WalkSpeed;
		motion = MotionLeftWalk;
	}
	else if (GamePad::state(GamePad::Right))
	{
		side_speed = -WalkSpeed;
		motion = MotionRightWalk;
	}
	if (CheckHitKey(KEY_INPUT_T) ||
		GamePad::state(GamePad::RightButton))
	{
		yaw_speed = 2.0f;
	}
	else if (CheckHitKey(KEY_INPUT_Y) ||
		GamePad::state(GamePad::LeftButton))
	{
		yaw_speed = -2.0f;
	}

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
	StaticMesh::transform(mesh_.bone_matrix(104));//19番が武器用の手のボーン
	StaticMesh::draw();
}
