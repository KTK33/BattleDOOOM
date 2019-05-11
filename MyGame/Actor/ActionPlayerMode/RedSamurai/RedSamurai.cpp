#include "RedSamurai.h"
#include "../Actor/PlayerBullet/PlayerBullet.h"
#include "../../ActorGroup.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
#include "../Texture/Sprite.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Actor/Player/PlayerItemBox/PlayerItemBox.h"
#include "RedSamuraiMotionNum.h"
#include "Arrow/ArrowAttack.h"
#include "../Actor/EnemyAttackCollison/EnemyAttackCollison.h"

RedSamurai::RedSamurai(int model, int sward, int arrow, int quiver, IWorld * world, const Vector3 & position, Matrix & rotation, std::weak_ptr<Actor> ui, const IBodyPtr & body) :
	Actor(world, "RedSamurai", position, body),
	Initbody{ body },
	m_ui{ ui },
	player_{nullptr},
	mesh_{ model,sward },
	sword_{ sward },
	arrow_{ arrow },
	quiver_{ quiver },
	state_{ RedSamuraiState::RedSamuraiIdel },
	before_state_{ RedSamuraiState::NONE },
    motion_{RedSamuraiMotionNum::MotionRedSamuraiIdel},
	before_motion_{motion_},
	state_timer_{ 0.0f },
	mSwordPos{ 38 },
	mArrowPos{ 76 },
	mQuiverPos{ 82 },
	DeadCheck{ false },
	mAttackTime{ 180.0f },
	mAttackTimeInit{mAttackTime},
	mAttacktype{ 0 }
{
	rotation_ = rotation;
	initialize();
}

void RedSamurai::initialize()
{
	mesh_.transform(Getpose());
	hp_ = PlayerHP;

	velocity_ = Vector3::Zero;

	change_state(RedSamuraiState::RedSamuraiIdel, RedSamuraiMotionNum::MotionRedSamuraiIdel);
}

void RedSamurai::update(float deltaTime)
{
	collision();

	if (world_->GetPauseCheck() == true || DeadCheck) return;

	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	Motion(deltaTime);
	mesh_.change_motion(motion_);

	getPlayer();
	if(state_ != RedSamuraiState::RedSamuraiAttack) rotation_ *= PlayerLook();
	if(state_ == RedSamuraiState::RedSamuraiIdel) AttackTimeCheck(deltaTime);

	m_ui.lock()->receiveMessage(EventMessage::SAMURAI_HP, reinterpret_cast<void*>(&hp_));

	//velocity_ = Vector3::Zero;
	velocity_ += Vector3::Up * -gravity;
	position_ += velocity_;

	velocity_ *= 0.8f;
	if (velocity_.Length() < 0.01f) {
		velocity_ = 0.0f;
	}
	if (Floorcollide) gravity = 0.0f;
	else gravity = 9.8f*0.1f;

	if (hp_ <= 0)
	{
		change_state(RedSamuraiState::RedSamuraiDead, RedSamuraiMotionNum::MotionRedSamuraiDead);
		GameDataManager::getInstance().SetDeadBossEnemy(true);
	}

	if (state_ != RedSamuraiState::RedSamuraiAttack) {
		mAttacktype = 0;
	}

}

void RedSamurai::draw() const
{
	mesh_.draw();
	draw_weapon();

	//SetFontSize(32);
	//DrawFormatString(1400, 450, GetColor(255, 0, 0), "%f", position_.x);
	//DrawFormatString(1400, 550, GetColor(255, 0, 0), "%f", position_.y);
	//DrawFormatString(1400, 650, GetColor(255, 0, 0), "%f", position_.z);
	//DrawFormatString(1400, 700, GetColor(255, 0, 0), "%i", mSwordPos);
	//SetFontSize(16);
}

void RedSamurai::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (int*)&hitdir);
}

void RedSamurai::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_PLAYER)
	{
		//Hit(*(Vector3*)param);
	}

	if (message == EventMessage::HIT_PLAYER_PUNCH)
	{
		hp_ = hp_ - *static_cast<int*>(param);
	}

}

void RedSamurai::getPlayer()
{
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void RedSamurai::collision()
{
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		position_.x = result.x;
		position_.z = result.z;
		Stagecollide = true;
	}
	else {
		Stagecollide = false;
	}

	//床との接地判定
	if (floor(result)) {
		Floorcollide = true;
		position_ = result + rotation_.Up()*(body_->length()*0.7f + body_->radius()*0.7f);
	}
	else {
		Floorcollide = false;
	}
}

void RedSamurai::change_state(RedSamuraiState::State state, int motion)
{
	before_motion_ = motion_;
	motion_ = motion;
	before_state_ = state_;
	state_ = state;
	state_timer_ = 0.0f;
}

void RedSamurai::AttackTimeCheck(float deltaTime)
{
	mAttackTime -= deltaTime;
	if (mAttackTime < 0)
	{
		AttackBehavior();
		mAttackTime = mAttackTimeInit;
		return;
	}

	Movement(deltaTime);
}

void RedSamurai::AttackSystem()
{
	switch (mAttacktype)
	{
	case 1 :
		if (state_timer_ == 20.0f)AttackCollision(15, 1, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
		if (state_timer_ == 40.0f)AttackCollision(15, 2, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
		if (state_timer_ == 60.0f)AttackCollision(15, 2, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
		break;
	default:
		break;
	}
}

void RedSamurai::AttackBehavior()
{
	if (GetPlayerDistance() >= 50.0f)//プレイヤーとの距離が50以上なら
	{
		change_state(RedSamuraiState::RedSamuraiAttack, RedSamuraiMotionNum::MotionRedSamuraiArrowAttack);
		world_->add_actor(ActorGroup::EnemyBullet, std::make_shared<ArrowAttack>(52,world_, Vector3{ position_.x,position_.y + 13.0f,position_.z } +rotation_.Forward() * 4 + rotation_.Right() * 3));
		mArrowPos = 38;
	}
	else
	{
		change_state(RedSamuraiState::RedSamuraiAttack, RedSamuraiMotionNum::MotionRedSamuraiAttack1);
		mAttacktype = 1;
	}
}

void RedSamurai::AttackCollision(int deadTime, int attackParam, Vector3 spot, float len, float rad)
{
	auto AttackPunch = std::make_shared<EnemyAttackCollison>(world_, Vector3{ position_ + Getpose().Forward() * 10 },
		std::make_shared<BoundingCapsule>(spot, Matrix::Identity, len, rad));
	world_->add_actor(ActorGroup::EnemyBullet, AttackPunch);
	AttackPunch->SetParam(false, deadTime, attackParam);
}


Matrix RedSamurai::PlayerLook()
{
	//ターゲット方向に少しずつ向きを変える Clampで無理やり角度(-TurnAngle～TurnAngle)内に
	const auto angle = MathHelper::Clamp(PlayerDirection(player_, position_, rotation_), -2.5f, 2.5f);
	return  Matrix::CreateRotationY(angle);
}

float RedSamurai::GetPlayerDistance()
{
	const float playerdistance = Vector3::Distance(position_, player_->Getposition());
	return playerdistance;
}

void RedSamurai::Movement(float deltaTime)
{
	if (GetPlayerDistance() <= 10.0f) return;
	motion_ = RedSamuraiMotionNum::MotionRedSamuraiForWard;
	const Vector3 playervec = Vector3(player_->Getposition().x - position_.x, player_->Getposition().y - position_.y, player_->Getposition().z - position_.z).Normalize();
	position_ += playervec * WalkSpeed;
}

void RedSamurai::Motion(float deltaTime)
{
	state_timer_ += 0.5f;

	if (state_ == RedSamuraiState::RedSamuraiAttack) {
		AttackSystem();
	}

	if (state_timer_ > mesh_.motion_end_time() - 5)
	{
		switch (state_) {
		case RedSamuraiState::RedSamuraiAttack:
			change_state(RedSamuraiState::RedSamuraiIdel, RedSamuraiMotionNum::MotionRedSamuraiIdel); break;
		case RedSamuraiState::RedSamuraiDead:
			DeadCheck = true; break;
		default: break;
		};

		mArrowPos = 76;
	}
}


void RedSamurai::draw_weapon() const
{
	StaticMesh::bind(sword_);
	StaticMesh::transform(mesh_.bone_matrix(mSwordPos));
	StaticMesh::draw();

	StaticMesh::bind(arrow_);
	StaticMesh::transform(mesh_.bone_matrix(mArrowPos));
	StaticMesh::draw();

	StaticMesh::bind(quiver_);
	StaticMesh::transform(mesh_.bone_matrix(mQuiverPos));
	StaticMesh::draw();
}

void RedSamurai::Hit(const Vector3 & dir)
{
	const Vector3 dir_ = Vector3::Normalize(dir);
	//アクターからプレイヤーの方向に移動
	velocity_ = Vector3::Up * 7.0f + Vector3{ dir_.x,0.f,dir_.z } *2.0f;
	velocity_.x = Vector3::Up.x * 7.0f + dir_.x*2.0f;
	velocity_.z = Vector3::Up.z * 7.0f + dir_.z*2.0f;
	velocity_.y = 0.0f;
	//collide = true;
}
