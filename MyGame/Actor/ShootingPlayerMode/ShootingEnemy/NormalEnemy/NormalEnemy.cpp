#include "NormalEnemy.h"
#include <memory>
#include "../Scene/GameData/GameDataManager.h"
#include "../Actor/ShootingPlayerMode/ItemActor/BulletItem/BulletItem.h"
#include "../Actor/ShootingPlayerMode/ItemActor/ItemCreater/ItemCreater.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/EnemyHeadShot/EnemyHeadShot.h"
#include "../Actor/CommonUIActor/Effect2D/Effect2D.h"
#include "../Sound/Sound.h"

NormalEnemy::NormalEnemy(int model, IWorld * world, const Vector3 & position,const Matrix & rotation, std::weak_ptr<Actor> m_ui,const IBodyPtr & body) :
	Actor(world, "NormalEnemy", position, body),
	mesh_{ model },
	state_{ NormalEnemyState::IDLE },
	state_timer_{ 0.0f },
	motion_{MotionNormalEnemyIdel},
	m_UI{m_ui},
	invinciblyCheck{ false },
	invinciblyTime{ 60 },
	roarCheck{ false },
	deadCheck{false},
	alreadyHS{false}
{
	rotation_ = rotation;
	mesh_.transform(Getpose());

	hp_ = 3;
	maxHp = hp_;

	DamageParam = 1;

	ActorSystem::TransparenceInit();

	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void NormalEnemy::initialize()
{
}

void NormalEnemy::update(float deltaTime)
{
	if (!alreadyHS)
	{
		auto EH = new_actor<EnemyHeadShot>(world_, position_, weak_from_this());
		world_->add_actor(ActorGroup::EnemyHead, EH);
		m_HS = EH;

		alreadyHS = true;
	}
	if (world_->GetPauseCheck() == false)
	{
		mesh_.update(deltaTime);
		mesh_.transform(Getpose());
		mesh_.change_motion(motion_);
		update_state(deltaTime);

		Delay();
	}
	if (m_HS.expired()) return;
	m_HS.lock()->receiveMessage(EventMessage::GETENEMYPOS, reinterpret_cast<void*>(&(position_ + HSPos)));

	velocity_ += Vector3::Up * -gravity;
	position_ += velocity_;
	velocity_ *= 0.8f;
	if (velocity_.Length() < 0.01f) {
		velocity_ = 0.0f;
	}
	collision();
	if (Floorcollide) gravity = 0.0f;
	else gravity = 9.8f*0.1f;

	if (invinciblyCheck) {
		ActorTransparence();
	}
	else {
		TransparenceInit();
	}

	prevPosition_ = position_;
}

void NormalEnemy::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();
}

void NormalEnemy::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (void*)&hitdir);
}
//メッセージを受け取る
void NormalEnemy::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_PLAYER)
	{
		hit_player(*static_cast<Vector3*>(param));
	}
	if (message == EventMessage::DAMAGEPARAM)
	{
		DamageParam = *static_cast<int*>(param);
	}
	if (!invinciblyCheck)
	{
		if (message == EventMessage::HIT_BALL)
		{
			hp_ = hp_ - DamageParam;
			change_state(NormalEnemyState::DAMAGE, MotionNormalEnemyDamage);
			invinciblyCheck = true;

			world_->add_actor(ActorGroup::Effect, new_actor<Effect2D>(world_, *static_cast<Vector3*>(param),1.0f, SPRITE_ID::EFFECT_BULLETHIT));
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DAMAGEENEMY_SE);
		}
		if (message == EventMessage::HIT_BALL_HEAD)
		{
			hp_ = hp_ - 3;
			change_state(NormalEnemyState::DAMAGE, MotionNormalEnemyDamage);
			invinciblyCheck = true;
			world_->add_actor(ActorGroup::Effect, new_actor<Effect2D>(world_, *static_cast<Vector3*>(param),1.0f, SPRITE_ID::EFFECT_BULLETHIT));
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DAMAGEENEMY_SE);
		}

		if (message == EventMessage::HIT_PLAYER_PUNCH)
		{
			hp_ = hp_ - *static_cast<int*>(param);
			change_state(NormalEnemyState::DAMAGE, MotionNormalEnemyDamage);
			invinciblyCheck = true;
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::ATTACK_SE);
		}


	}
}

void NormalEnemy::collision()
{
	//ぶつかったか
	Vector3 result;
	////壁とぶつけてから
	//if (field(result)) {
	//	position_.x = result.x;
	//	position_.z = result.z;
	//	Stagecollide = true;
	//}
	//else
	//{
	//	Stagecollide = false;
	//}

	//床との接地判定
	if (floor(result)) {
		Floorcollide = true;
		position_ = result + rotation_.Up()*(body_->length()*0.5f + body_->radius()*0.5f);
	}
	else {
		Floorcollide = false;
	}
}

void NormalEnemy::update_state(float deltaTime)
{
	switch (state_)
	{
	case NormalEnemyState::IDLE:		Idle();		break;
	case NormalEnemyState::PUNCH:	Punch();	break;
	case NormalEnemyState::ROAR:		Roar();		break;
	case NormalEnemyState::MOVE:		Move();		break;
	case NormalEnemyState::DAMAGE:	Damage();	break;
	case NormalEnemyState::DEAD:		Dead();		break;
	default: break;
	}
}

void NormalEnemy::Idle()
{
	change_state(NormalEnemyState::IDLE, MotionNormalEnemyIdel);
}

void NormalEnemy::Roar()
{
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::ENEMYDOAR_SE);
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time() + 100)
	{
		change_state(NormalEnemyState::MOVE, MotionNormalEnemyMove);
	}
}

void NormalEnemy::Move()
{
	state_timer_ += 1.0f;
	if (state_timer_ <= 30 && state_timer_ >= 10)
	{
		WalkSpeed = 0.005f;
	}
	else
	{
		WalkSpeed = max(WalkSpeed - 0.001f, 0.0f);
	}

	if (state_timer_ >= mesh_.motion_end_time())
	{
		state_timer_ = 0.0f;
	}

	position_ = Vector3::Lerp(position_, player_->Getposition(), WalkSpeed);

	//ターゲット方向に少しずつ向きを変える Clampで無理やり角度(-TurnAngle～TurnAngle)内に
	const auto angle = MathHelper::Clamp(PlayerDirection(player_, position_, rotation_), -2.5f, 2.5f);

	rotation_ *= Matrix::CreateRotationY(angle);

	if (Vector3::Distance(position_,player_->Getposition()) <= AttackDis && 
		(angle <= 0.1f || angle >= -0.1f) && 
		GameDataManager::getInstance().GetPlayerDead() == false)
	{
		change_state(NormalEnemyState::PUNCH, MotionNormalEnemyPunch);
	}
}

void NormalEnemy::Punch()
{
	state_timer_ += 1.0f;
	if (state_timer_ == 80)
	{
		auto Bullet = std::make_shared<EnemyAttackCollison>(world_, Vector3{ position_ + Getpose().Forward() * 6 },
			std::make_shared<BoundingCapsule>(Vector3{ 0.0f,10.0f,0.0f }, Matrix::Identity, 3.0f, 3.0f));
		world_->add_actor(ActorGroup::EnemyBullet, Bullet);
		Bullet->SetParam(false, static_cast<int>(mesh_.motion_end_time()) / 2, 1);
	}
	if (state_timer_ >= mesh_.motion_end_time())
	{
		change_state(NormalEnemyState::MOVE, MotionNormalEnemyMove);
	}
}

void NormalEnemy::Damage()
{
	state_timer_ += 1.0f;
	if (!roarCheck)
	{
		if (state_timer_ >= mesh_.motion_end_time() + 50)
		{
			change_state(NormalEnemyState::ROAR, MotionNormalEnemyRoar);
			roarCheck = true;
		}
	}
	else
	{
		if (state_timer_ >= mesh_.motion_end_time() + 50)
		{
			change_state(NormalEnemyState::MOVE, MotionNormalEnemyMove);
		}

	}
}

void NormalEnemy::Dead()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time() + 100)
	{
		//world_->send_message(EventMessage::DUMMY_DEAD_ENEMY, nullptr);
		world_->add_actor(ActorGroup::Item, std::make_shared<ItemCreater>(world_, position_));
		deadCheck = true;

		m_HS.lock()->receiveMessage(EventMessage::DEAD_DUMMY_ENEMY, nullptr);
		m_UI.lock()->receiveMessage(EventMessage::DUMMY_DEAD_ENEMY, nullptr);
		die();
	}
}

void NormalEnemy::hit_player(const Vector3 & dir)
{
	//die();
}

void NormalEnemy::deadAction()
{
	world_->send_message(EventMessage::DUMMY_DEAD_ENEMY, nullptr);
	die();

}

void NormalEnemy::change_state(NormalEnemyState::State state, int motion)
{
	motion_ = motion;
	state_ = state;
	state_timer_ = 0.0f;
}

void NormalEnemy::Action(NormalEnemyState::State state)
{
}

void NormalEnemy::Delay()
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
			motion_ = MotionNormalEnemyDead;
			state_ = NormalEnemyState::DEAD;
		}
	}
}
