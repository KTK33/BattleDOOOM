#include "DummyEnemy.h"
#include "../../Scene/GameData/GameDataManager.h"
#include "../ItemActor/BulletItem.h"
#include "../ItemActor/ItemCreater.h"
#include "EnemyHeadShot.h"
#include <memory>
#include "../UIActor/Effect.h"

DummyEnemy::DummyEnemy(int model, IWorld * world, const Vector3 & position,const Matrix & rotation, const IBodyPtr & body) :
	Actor(world, "DummyEnemy", position, body),
	mesh_{ model },
	state_{ DummyEnemyState::IDLE },
	state_timer_{ 0.0f },
	invinciblyCheck{ false },
	invinciblyTime{ 60 },
	roarCheck{ false },
	deadCheck{false}
{
	rotation_ = rotation;
	mesh_.transform(Getpose());

	hp_ = 3;
	maxHp = hp_;

	auto EH = new_actor<EnemyHeadShot>(world_, position_,weak_from_this());
	world_->add_actor(ActorGroup::Enemy, EH);
	m_HS = EH;

	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void DummyEnemy::initialize()
{
}

void DummyEnemy::update(float deltaTime)
{
	if (world_->GetPauseCheck() == false)
	{
		mesh_.update(deltaTime);
		mesh_.transform(Getpose());
		mesh_.change_motion(motion_);
		update_state(deltaTime);

		Delay();
	}
	if (m_HS.expired()) return;
	m_HS.lock()->receiveMessage(EventMessage::GETENEMYPOS, (void*)&position_);

	//collision();
}

void DummyEnemy::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}

void DummyEnemy::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (void*)&hitdir);
}
//メッセージを受け取る
void DummyEnemy::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_PLAYER)
	{
		hit_player(*(Vector3*)param);
	}
	if (!invinciblyCheck)
	{
		if (message == EventMessage::HIT_BALL)
		{
			//hp_ = hp_ - *(int*)param;
			hp_ = hp_ - 1;
			change_state(DummyEnemyState::DAMAGE, MotionDummyDamage);
			invinciblyCheck = true;

			world_->add_actor(ActorGroup::Effect, new_actor<Effect>(world_, *(Vector3*)param ,Vector3::Distance(position_,player_->Getposition()),SPRITE_ID::EFFECT_BULLETHIT));

		}
		if (message == EventMessage::HIT_BALL_HEAD)
		{
			hp_ = hp_ - *(int*)param;
			change_state(DummyEnemyState::DAMAGE, MotionDummyDamage);
			invinciblyCheck = true;
		}

		if (message == EventMessage::HIT_PLAYER_PUNCH)
		{
			hp_ = hp_ - *(int*)param;
			change_state(DummyEnemyState::DAMAGE, MotionDummyDamage);
			invinciblyCheck = true;
		}


	}
	//if (message == EventMessage::DEAD_DUMMY_ENEMY){
	//	die();
	//}
}

void DummyEnemy::collision()
{
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		position_ = result;
	}

	//床との接地判定
	if (floor(result)) {
		position_ = result + rotation_.Up() *(body_->length()*0.5f + body_->radius());
	}

}

void DummyEnemy::update_state(float deltaTime)
{
	switch (state_)
	{
	case DummyEnemyState::IDLE:		Idle();		break;
	case DummyEnemyState::PUNCH:	Punch();	break;
	case DummyEnemyState::ROAR:		Roar();		break;
	case DummyEnemyState::MOVE:		Move();		break;
	case DummyEnemyState::DAMAGE:	Damage();	break;
	case DummyEnemyState::DEAD:		Dead();		break;
	default: break;
	}
}

void DummyEnemy::Idle()
{
	change_state(DummyEnemyState::IDLE, MotionDummyIdel);
}

void DummyEnemy::Roar()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time() + 100)
	{
		change_state(DummyEnemyState::MOVE, MotionDummyMove);
	}
}

void DummyEnemy::Move()
{
	position_ = Vector3::Lerp(position_, player_->Getposition(), WalkSpeed);

	//ターゲット方向に少しずつ向きを変える Clampで無理やり角度(-TurnAngle～TurnAngle)内に
	const auto angle = MathHelper::Clamp(PlayerDirection(player_, position_, rotation_), -2.5f, 2.5f);
	rotation_ *= Matrix::CreateRotationY(angle);

	if (Vector3::Distance(position_,player_->Getposition()) <= AttackDis && 
		angle == 0)
	{
		change_state(DummyEnemyState::PUNCH, MotionDummyPunch);
	}
}

void DummyEnemy::Punch()
{
	state_timer_ += 1.0f;
	if (state_timer_ == 80)
	{
		auto Bullet = std::make_shared<EnemyAttack>(world_, Vector3{ position_ + Getpose().Forward() * 6 },
			std::make_shared<BoundingCapsule>(Vector3{ 0.0f,10.0f,0.0f }, Matrix::Identity, 3.0f, 3.0f));
		world_->add_actor(ActorGroup::EnemyBullet, Bullet);
		Bullet->SetdeadTime((int)mesh_.motion_end_time() / 2);
		Bullet->SetAttackParam(1);
	}
	if (state_timer_ >= mesh_.motion_end_time())
	{
		change_state(DummyEnemyState::MOVE, MotionDummyMove);
	}
}

void DummyEnemy::Damage()
{
	state_timer_ += 1.0f;
	if (!roarCheck)
	{
		if (state_timer_ >= mesh_.motion_end_time() + 50)
		{
			change_state(DummyEnemyState::ROAR, MotionDummyRoar);
			roarCheck = true;
		}
	}
	else
	{
		if (state_timer_ >= mesh_.motion_end_time() + 50)
		{
			change_state(DummyEnemyState::MOVE, MotionDummyMove);
		}

	}
}

void DummyEnemy::Dead()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		world_->send_message(EventMessage::DUMMY_DEAD_ENEMY, nullptr);
		world_->add_actor(ActorGroup::Item, std::make_shared<ItemCreater>(world_, position_));
		deadCheck = true;
		//if (m_HS.expired()) die(); return;
		//m_HS.lock()->receiveMessage(EventMessage::DEAD_DUMMY_ENEMY, nullptr);
		die();
	}
}

void DummyEnemy::hit_player(const Vector3 & dir)
{
	//die();
}

void DummyEnemy::deadAction()
{
	world_->send_message(EventMessage::DUMMY_DEAD_ENEMY, nullptr);
	die();

}

void DummyEnemy::change_state(DummyEnemyState::State state, int motion)
{
	motion_ = motion;
	state_ = state;
	state_timer_ = 0.0f;
}

void DummyEnemy::Action(DummyEnemyState::State state)
{
}

void DummyEnemy::Delay()
{
	if (invinciblyCheck) {
		if (hp_ > 0)
		{
			invinciblyTime--;
			if (invinciblyTime <= 0)
			{
				invinciblyCheck = false;
				invinciblyTime = 60;
			}
		}
		else {
			motion_ = MotionDummyDead;
			state_ = DummyEnemyState::DEAD;
		}
	}
}
