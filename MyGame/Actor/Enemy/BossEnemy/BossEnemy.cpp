#include "BossEnemy.h"
#include "../Actor/UIActor/BossEnemyUI/BossEnemyUI.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Texture/Sprite.h"
#include "../Actor/UIActor/Effect2D/Effect2D.h"
#include "../Sound/Sound.h"

BossEnemy::BossEnemy(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body) :
	Actor(world, "BossEnemy", position, body),
	mesh_(model),
	state_{BossEnemyState::IDLE},
	state_timer_{ 0.0f },
	invinciblyCheck{ false },
	invinciblyTime{ 60 },
	Ikari{false},
	FireCheck{false},
	FireCount{0},
	WalkVal{1.0f}
{
	rotation_ *= Matrix::CreateRotationY(180.0f);
	mesh_.transform(Getpose());

	auto UI = new_actor<BossEnemyUI>(world_);
	world_->add_actor(ActorGroup::UI, UI);
	m_ui = UI;

	ActorSystem::TransparenceInit();

	hp_ = 10;

	DamageParam = 1;

	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void BossEnemy::initialize()
{
}

void BossEnemy::update(float deltaTime)
{
	if (world_->GetPauseCheck() == false)
	{
		mesh_.update(deltaTime);
		mesh_.transform(Getpose());
		mesh_.change_motion(motion_);
		update_state(deltaTime);

		Delay();
	}

	velocity_ += Vector3::Up * -gravity;
	position_ += velocity_;
	velocity_ *= 0.8f;
	if (velocity_.Length() < 0.01f) {
		velocity_ = 0.0f;
	}
	collision();
	if (Floorcollide) gravity = 0.0f;
	else gravity = 9.8f*0.1f;

	if (hp_ <= 5){
		Ikari = true;
	}

	FireCount++;

	if (FireCount >= 600)
	{
		FireCheck = true;
	}

	m_ui.lock()->receiveMessage(EventMessage::BOSSHP, (int*)&hp_);

	if (invinciblyCheck) {
		ActorTransparence();
	}
	else {
		TransparenceInit();
	}

}

void BossEnemy::draw() const
{
	mesh_.draw();
	body_->transform(Getpose())->draw();

	//HP
	Sprite::GetInstance().Draw(SPRITE_ID::BOSSHP_UI, Vector2(0, WINDOW_HEIGHT -  Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_UI).y));
	Sprite::GetInstance().DrawPart(SPRITE_ID::BOSSHP_GAUGE, Vector2(492, WINDOW_HEIGHT - 70), 0, 0,
		Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_GAUGE).x / PlayerHP * hp_, Sprite::GetInstance().GetSize(SPRITE_ID::BOSSHP_GAUGE).y);

}

void BossEnemy::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (void*)&hitdir);
}

void BossEnemy::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::DAMAGEPARAM)
	{
		DamageParam = *(int*)param;
	}
	if (!invinciblyCheck){
		if (message == EventMessage::HIT_BALL){
			hp_ = hp_ - DamageParam;
			if (state_ != BossEnemyState::FIRE_BEFO)
			{
				change_state(BossEnemyState::DAMAGE, MotionBossDamage);
			}
			invinciblyCheck = true;

			world_->add_actor(ActorGroup::Effect, new_actor<Effect2D>(world_, *(Vector3*)param,1.0f, SPRITE_ID::EFFECT_BULLETHIT));
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DAMAGEENEMY_SE);
		}
		if (message == EventMessage::HIT_PLAYER_PUNCH){
			hp_ = hp_ - *(int*)param;
			if (state_ != BossEnemyState::FIRE_BEFO) {
				change_state(BossEnemyState::DAMAGE, MotionBossDamage);
			}
			invinciblyCheck = true;
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::ATTACK_SE);
		}
	}
}

void BossEnemy::collision()
{
	//‚Ô‚Â‚©‚Á‚½‚©
	Vector3 result;
	////•Ç‚Æ‚Ô‚Â‚¯‚Ä‚©‚ç
	//if (field(result)) {
	//	position_.x = result.x;
	//	position_.z = result.z;
	//	Stagecollide = true;
	//}
	//else
	//{
	//	Stagecollide = false;
	//}

	//°‚Æ‚ÌÚ’n”»’è
	if (floor(result)) {
		Floorcollide = true;
		position_ = result + rotation_.Up()*(body_->length()*0.5f + body_->radius()*0.5f);
	}
	else {
		Floorcollide = false;
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
	case BossEnemyState::FIRE_BEFO:	AttackFireBefo();	break;
	case BossEnemyState::FIRE:	AttackFire();	break;
	case BossEnemyState::FIRE_AFTE:	AttackFireAfte();	break;
	case BossEnemyState::DAMAGE:Damage();	break;
	case BossEnemyState::DEAD:	Dead();		break;
	default:break;
	}
}

void BossEnemy::Idle()
{
	change_state(BossEnemyState::WALK, MotionBossWalk);
}

void BossEnemy::MoveWalk()
{
	if (Ikari){
		WalkVal = 6.0f;
		position_ = Vector3::Lerp(position_, player_->Getposition(), WalkSpeed*WalkVal);
		if (FireCheck)
		{
			change_state(BossEnemyState::FIRE_BEFO, MotionBossFireBefo);
		}
	}
	else{
		WalkVal = 3.0f;
		position_ = Vector3::Lerp(position_, player_->Getposition(), WalkSpeed*WalkVal);
	}

	//ƒ^[ƒQƒbƒg•ûŒü‚É­‚µ‚¸‚ÂŒü‚«‚ð•Ï‚¦‚é Clamp‚Å–³—‚â‚èŠp“x(-TurnAngle`TurnAngle)“à‚É
	const auto angle = MathHelper::Clamp(PlayerDirection(player_,position_,rotation_), -2.5f, 2.5f);
	rotation_ *= Matrix::CreateRotationY(angle);

	if (Vector3::Distance(position_, player_->Getposition()) <= AttackDis 
		&& (angle <= 0.1f || angle >= -0.1f) &&
		GameDataManager::getInstance().GetPlayerDead() == false)
	{
		change_state(BossEnemyState::PUNCH, MotionBossPunch);
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
		auto Bullet = std::make_shared<EnemyAttackCollison>(world_, Vector3{ position_ + Getpose().Forward() * 6 },
			std::make_shared<BoundingCapsule>(Vector3{ 0.0f,5.0f,0.0f }, Matrix::Identity, 10.0f, 5.0f));
		world_->add_actor(ActorGroup::EnemyBullet, Bullet);
		Bullet->SetdeadTime(mesh_.motion_end_time()/2);
		Bullet->SetAttackParam(3);
	}
	if (state_timer_ >= mesh_.motion_end_time())
	{
		if (Ikari) {
			change_state(BossEnemyState::WALK, MotionBossRun);
		}
		else {
			change_state(BossEnemyState::WALK, MotionBossWalk);
		}
	}
}

void BossEnemy::AttackFireBefo()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time() + 60)
	{
		change_state(BossEnemyState::FIRE, MotionBossPunch2);
	}

}

void BossEnemy::AttackFire()
{
	state_timer_ += 1.0f;
	if (state_timer_ == 20)
	{
		auto enemyFire = std::make_shared<EnemyAttackFire>(8,world_, Vector3{ position_.x,position_.y + 15.0f,position_.z } +rotation_.Forward() * 10);
		world_->add_actor(ActorGroup::EnemyBullet, enemyFire);
		enemyFire->GetEnemyForward(Getpose().Forward());
	}
	if (state_timer_ >= mesh_.motion_end_time() + 50)
	{
		FireCheck = false;
		FireCount = 0;
		change_state(BossEnemyState::WALK, MotionBossFireAfte);
	}
}

void BossEnemy::AttackFireAfte()
{
}

void BossEnemy::Damage()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time())
	{
		if (Ikari) {
			change_state(BossEnemyState::WALK, MotionBossRun);
		}
		else {
			change_state(BossEnemyState::WALK, MotionBossWalk);
		}
	}
}

void BossEnemy::Dead()
{
	state_timer_ += 1.0f;
	if (state_timer_ >= mesh_.motion_end_time() + 10)
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