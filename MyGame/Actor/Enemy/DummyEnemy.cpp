#include "DummyEnemy.h"
#include "../../Scene/GameData/GameDataManager.h"

DummyEnemy::DummyEnemy(int model, IWorld * world, const Vector3 & position,const Matrix & rotation, const IBodyPtr & body) :
	Actor(world, "DummyEnemy", position, body),
	mesh_{ model },
	state_{ DummyEnemyState::IDLE },
	state_timer_{ 0.0f },
	invinciblyCheck{ false },
	invinciblyTime{ 60 },
	roarCheck{ false }
{
	rotation_ = rotation;
	mesh_.transform(Getpose());

	hp_ = 3;
	maxHp = hp_;
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

}

void DummyEnemy::initialize()
{
}

void DummyEnemy::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(motion_);
	update_state(deltaTime);

	Delay();
}

void DummyEnemy::draw() const
{
	mesh_.draw();
	//body_->transform(Getpose())->draw();

	DrawFormatString(500, 500, GetColor(255, 255, 255), "%f", state_timer_);
	DrawFormatString(500, 600, GetColor(255, 255, 255), "%f", mesh_.motion_end_time());

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
			hp_ = hp_ - 1;
			change_state(DummyEnemyState::DAMAGE, MotionDummyDamage);
			invinciblyCheck = true;
		}

	}
	if (message == EventMessage::DEAD_DUMMY_ENEMY){
		die();
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

	if (Vector3::Distance(position_,player_->Getposition()) <= AttackDis)
	{
		change_state(DummyEnemyState::PUNCH, MotionDummyPunch);
	}

	//ターゲット方向に少しずつ向きを変える Clampで無理やり角度(-TurnAngle～TurnAngle)内に
	const auto angle = MathHelper::Clamp(PlayerDirection(player_, position_, rotation_), -2.5f, 2.5f);
	rotation_ *= Matrix::CreateRotationY(angle);
}

void DummyEnemy::Punch()
{
	state_timer_ += 1.0f;
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
