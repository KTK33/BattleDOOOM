#include "BossEnemy.h"
#include "../../Scene/GameData/GameDataManager.h"

BossEnemy::BossEnemy(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body) :
	Actor(world, "BossEnemy", position, body),
	mesh_(model),
	state_{BossEnemyState::IDLE},
	state_timer_{ 0.0f },
	invinciblyCheck{ false },
	invinciblyTime{ 60 }
{
	rotation_ *= Matrix::CreateRotationY(180.0f);
	mesh_.transform(Getpose());

	hp_ = 10;
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void BossEnemy::initialize()
{
}

void BossEnemy::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(motion_);
	update_state(deltaTime);

	Delay();
}

void BossEnemy::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}

void BossEnemy::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (void*)&hitdir);
}

void BossEnemy::receiveMessage(EventMessage message, void * param)
{
	if (!invinciblyCheck)
	{
		if (message == EventMessage::HIT_BALL)
		{
			hp_ = hp_ - 1;
			change_state(BossEnemyState::DAMAGE, MotionBossDamage);
			invinciblyCheck = true;
		}

	}
}

void BossEnemy::update_state(float deltaTime)
{
	switch (state_)
	{
	case BossEnemyState::IDLE:	Idle();		break;
	case BossEnemyState::WALK:  MoveWalk();	break;
	case BossEnemyState::RUN:	MoveRun();	break;
	case BossEnemyState::PUNCH:	Punch();	break;
	case BossEnemyState::DAMAGE:Damage();	break;
	case BossEnemyState::DEAD:	Dead();		break;
	default:break;
	}
}

void BossEnemy::Idle()
{
	change_state(BossEnemyState::IDLE, MotionBossIdel);
}

void BossEnemy::MoveWalk()
{
	position_ = Vector3::Lerp(position_, player_->Getposition(), WalkSpeed);

	//ƒ^[ƒQƒbƒg•ûŒü‚É­‚µ‚¸‚ÂŒü‚«‚ð•Ï‚¦‚é Clamp‚Å–³—‚â‚èŠp“x(-TurnAngle`TurnAngle)“à‚É
	const auto angle = MathHelper::Clamp(PlayerDirection(player_,position_,rotation_), -2.5f, 2.5f);
	rotation_ *= Matrix::CreateRotationY(angle);

	if (Vector3::Distance(position_, player_->Getposition()) <= AttackDis && 
		angle == 0)
	{
		if (hp_ <= hp_ / 2)
		{
			change_state(BossEnemyState::PUNCH, MotionBossPunch2);
		}
		else
		{
			change_state(BossEnemyState::PUNCH, MotionBossPunch);
		}
	}
}

void BossEnemy::MoveRun()
{
}

void BossEnemy::Punch()
{
	state_timer_ += 1.0f;

	if (state_timer_ == 60)
	{
		auto Bullet = std::make_shared<EnemyAttack>(world_, Vector3{ position_ + Getpose().Forward() * 6 },
			std::make_shared<BoundingCapsule>(Vector3{ 0.0f,5.0f,0.0f }, Matrix::Identity, 10.0f, 5.0f));
		world_->add_actor(ActorGroup::EnemyBullet, Bullet);
		Bullet->SetdeadTime(mesh_.motion_end_time()/2);
		Bullet->SetAttackParam(3);
	}
	if (state_timer_ >= mesh_.motion_end_time())
	{
		change_state(BossEnemyState::WALK, MotionBossWalk);
	}
}

void BossEnemy::Damage()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		change_state(BossEnemyState::WALK, MotionBossWalk);
	}
}

void BossEnemy::Dead()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		world_->send_message(EventMessage::BOSS_DEAD, nullptr);
		GameDataManager::getInstance().SetDeadBossEnemy(true);
		die();
	}
}

void BossEnemy::change_state(BossEnemyState::State state, int motion)
{
	motion_ = motion;
	state_ = state;
	state_timer_ = 0.0f;
}

void BossEnemy::hit_player(const Vector3 & dir)
{
}

void BossEnemy::deadAction()
{
	GameDataManager::getInstance().SetDeadBossEnemy(true);
	die();
}

void BossEnemy::Delay()
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
			motion_ = MotionBossDead;
			state_ = BossEnemyState::DEAD;
		}
	}
}