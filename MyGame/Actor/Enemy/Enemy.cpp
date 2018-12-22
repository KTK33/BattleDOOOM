#include "Enemy.h"

#include "../../World/IWorld.h"
#include "../ActorGroup.h"
#include "../../Fiield/Field.h"
#include "../PlayerBall/Ball.h"

Enemy::Enemy(int model, const Vector3 & position,IWorld& world) :
	//rotation_{ Matrix::Identity },
	//position_{ position },
	//velocity_{ 0.0f,0.0f,0.0f },
	mesh_{ model,EnemyMotionIdle },
	motion_{ EnemyMotionIdle },
	state_{ State::Idle },
	player_{nullptr}
{
	world_ = &world;
	name_ = "Enemy";
	position_ = position;
	body_ = BoundingSphere{ 1.0f,{ 0.0f,5.0f,0.0f } };
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	mesh_.transform(pose());
	timer_ = 0;
}

void Enemy::update(float delta_time)
{
	update_state(delta_time);
	mesh_.change_motion(motion_);
	mesh_.update(delta_time);
	mesh_.transform(pose());

	timer_++;
	if (timer_ == 200)
	{
		timer_ = 0;
		world_->add_actor(ActorGroup::Ball, new_actor<Ball>(2, *world_, Vector3(position_.x, position_.y + 10, position_.z)));
	}
}

void Enemy::draw() const
{
	mesh_.draw();

}

void Enemy::react(Actor& other)
{
	change_state(State::Damage, EnemyMotionDamage);
	//if (other.name() == "PlayerBullet")
	//{
	//	change_state(State::Damage, EnemyMotionDamage);
	//	//die();
	//}
}

//Matrix Enemy::pose() const
//{
//	return Matrix(rotation_).Translation(position_);
//}

void Enemy::update_state(float delta_time)
{
	switch (state_)
	{
	case Enemy::State::Idle:   idle(delta_time);   break;
	//case Enemy::State::Walk:   walk(delta_time); break;
	//case Enemy::State::Turn:   turn(delta_time);   break;
	//case Enemy::State::Damage: damage(delta_time); break;
	//case Enemy::State::Attack: attack(delta_time); break;
	};
	state_timer_ += delta_time;
}

void Enemy::change_state(State state, int motion)
{
	motion_ = motion;
	state_ = state;
	state_timer_ = 0.0f;
}

void Enemy::idle(float delta_time)
{
	if (is_attack())
	{
		change_state(State::Attack, EnemyMotionAttack);
		return;
	}
	if (is_walk())
	{
		change_state(State::Walk, EnemyMotionWalk);
		return;
	}
	if (is_turn())
	{
		int motion = (target_angle() >= 0.0f) ? EnemyMotionTurnLeft : EnemyMotionTurnRight;
		change_state(State::Turn, motion);
		return;
	}
	change_state(State::Idle, EnemyMotionIdle);
}

void Enemy::walk(float delta_time)
{
	//ターゲット方向に少しずつ向きを変える Clampで無理やり角度(-TurnAngle～TurnAngle)内に
	const auto angle = MathHelper::Clamp(target_angle(), -TurnAngle, TurnAngle);
	rotation_ *= Matrix::CreateRotationY(angle);
	//前に移動する
	rotation_.NormalizeRotationMatrix();
	position_ += rotation_.Forward() * WalkSpeed * delta_time;
	//攻撃するか
	if (is_attack())
	{//攻撃状態に遷移
		change_state(State::Attack, EnemyMotionAttack);
	}
}

void Enemy::turn(float delta_time)
{
	//アニメーション中かどうか
	if (state_timer_ < mesh_.motion_end_time())
	{
		//パッと向かないように設定
		const auto angle = (target_angle() >= 0.0f) ? TurnAngle : -TurnAngle;
		rotation_ *= Matrix::CreateRotationY(angle);
		rotation_.NormalizeRotationMatrix();
		return;
	}
	//アニメーションが終了したらアイドル状態へ
	idle(delta_time);
}

void Enemy::attack(float delta_time)
{
	//アニメーションが終了したか
	if (state_timer_ >= mesh_.motion_end_time())
	{
		//アイドル状態にする
		idle(delta_time);
	}
}

void Enemy::damage(float delta_time)
{
	//アニメーション中は何もしない
	if (state_timer_ < mesh_.motion_end_time())
	{
		return;
	}
	//背後から攻撃されたら振り向く
	if (std::abs(target_angle()) > 90.0f)
	{
		const auto motion = (target_angle() >= 0.0f) ? EnemyMotionTurnLeft : EnemyMotionTurnRight;
		change_state(State::Turn, motion);
		return;
	}
	idle(delta_time);
}

bool Enemy::is_turn() const
{
	return (target_distance() <= TurnDistance) && (std::abs(target_angle()) > 90.0f);
}

bool Enemy::is_attack() const
{
	return (target_distance() <= AttackDistance) && (std::abs(target_angle()) <= 20.0f);
}

bool Enemy::is_walk() const
{
	return std::abs(target_angle()) <= 100.0f;
}

float Enemy::target_angle() const
{
	const auto& to_target = player_->pose().Translation() - position_;
	const auto angle = Vector3::Angle(rotation_.Forward(), to_target);
	const auto& forward_cross_target = Vector3::Cross(rotation_.Forward(), to_target);
	return (forward_cross_target.y >= 0.0f) ? angle : -angle;
}

float Enemy::target_distance() const
{
	return Vector3::Distance(position_, player_->pose().Translation());
}
