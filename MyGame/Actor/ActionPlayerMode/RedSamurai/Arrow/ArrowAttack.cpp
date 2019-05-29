#include "ArrowAttack.h"
#include "../Sound/Sound.h"

ArrowAttack::ArrowAttack(int model, IWorld * world, const Vector3 & position, const IBodyPtr & body):
	Actor(world,"ArrowAttack",position,body),
	mesh_{ model }
{
	mesh_.transform(Getpose());

	player_ = world_->find_actor(ActorGroup::Player, "Player").get();

	Vector3 playerpos = player_->Getposition();
	playerpos.y = playerpos.y + 15.0f;
	plyaerVector = Vector3(playerpos.x - position_.x, playerpos.y - position_.y, playerpos.z - position_.z);

	Vector3 pos = position_;
	pos.y = pos.y + 15.0f;//プレイヤーの身長分を足す

	//プレイヤ―の向きに矢を向かせる
	rotation_ = Matrix::Invert(Matrix::CreateLookAt(pos, pos + plyaerVector, Vector3::Up) * Matrix::CreateRotationY(180));

	Sound::GetInstance().PlaySE(SE_ID::ARROW);
}


void ArrowAttack::update(float deltaTime)
{
	mesh_.update(deltaTime);
	//行列の設定
	mesh_.transform(Getpose());

	position_ += plyaerVector.Normalize() * 3.0f;

	collision();
}

void ArrowAttack::onCollide(Actor & other)
{
	int DamageVal = 1;
	other.receiveMessage(EventMessage::HIT_ENEMY_BULLET,  reinterpret_cast<void*>(&DamageVal));
}

void ArrowAttack::receiveMessage(EventMessage message, void * param){}

void ArrowAttack::draw() const
{
	mesh_.draw();
}

void ArrowAttack::collision()
{
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		die();
	}

	//床との接地判定
	if (floor(result)) {
		die();
	}
}

