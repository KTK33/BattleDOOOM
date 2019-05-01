#include "RedSamurai.h"
#include "../Actor/PlayerBullet/PlayerBullet.h"
#include "../../ActorGroup.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
#include "../Texture/Sprite.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Actor/Player/PlayerItemBox/PlayerItemBox.h"
#include "RedSamuraiMotionNum.h"

RedSamurai::RedSamurai(int model, int weapon, IWorld * world, const Vector3 & position, std::weak_ptr<Actor> ui, const IBodyPtr & body) :
	Actor(world, "Player", position, body),
	Initbody{ body },
	m_ui{ ui },
	mesh_{ model,weapon },
	weapon_{ weapon },
	state_{ RedSamuraiState::RedSamuraiIdel },
	before_state_{ RedSamuraiState::NONE },
	state_timer_{ 0.0f },
	mweaponPos{37},
	invinciblyCheck{ false },
	invinciblyTime{ 100 },
	DeadCheck{ false }
{
	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());
	hp_ = PlayerHP;

	velocity_ = Vector3::Zero;
}

void RedSamurai::initialize()
{
}

void RedSamurai::update(float deltaTime)
{
	if (world_->GetPauseCheck() == false) {
		if (!DeadCheck)
		{
			mesh_.update(deltaTime);
			mesh_.transform(Getpose());
			Motion(deltaTime);
			if (state_ == RedSamuraiState::RedSamuraiIdel)
			{
				Idle();
			}
			mesh_.change_motion(motion_);
			//Delay();
		}
	}

	world_->send_message(EventMessage::PLAYER_HP, (void*)&hp_);

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
}

void RedSamurai::draw() const
{
	mesh_.draw();
	draw_weapon();
}

void RedSamurai::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (void*)&hitdir);
}

void RedSamurai::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::HIT_PLAYER)
	{
		//Hit(*(Vector3*)param);
	}
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
		position_ = result + rotation_.Up()*(body_->length()*0.5f + body_->radius()*0.5f);
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

void RedSamurai::Idle()
{
	change_state(RedSamuraiState::RedSamuraiIdel, RedSamuraiMotionNum::MotionRedSamuraiIdel);
}

void RedSamurai::Motion(float deltaTime)
{
	state_timer_ += deltaTime / 2;
}

void RedSamurai::draw_weapon() const
{
	StaticMesh::bind(weapon_);
	StaticMesh::transform(mesh_.bone_matrix(mweaponPos));
	StaticMesh::draw();
}

void RedSamurai::Delay()
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
			motion_ = RedSamuraiMotionNum::Motion::MotionRedSamuraiIdel;
			state_ = RedSamuraiState::RedSamuraiIdel;
		}
	}
}

void RedSamurai::Hit(Vector3 & dir)
{
	Vector3 dir_ = Vector3::Normalize(dir);
	//アクターからプレイヤーの方向に移動
	velocity_ = Vector3::Up * 7.0f + Vector3{ dir_.x,0.f,dir_.z } *2.0f;
	velocity_.x = Vector3::Up.x * 7.0f + dir_.x*2.0f;
	velocity_.z = Vector3::Up.z * 7.0f + dir_.z*2.0f;
	velocity_.y = 0.0f;
	//collide = true;
}
