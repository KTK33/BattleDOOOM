#include "ArrowAttack.h"

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
	pos.y = pos.y + 15.0f;

	rotation_ = Matrix::Invert(Matrix::CreateLookAt(pos, pos + playerpos * Matrix::CreateRotationY(180), Vector3::Up));
}


void ArrowAttack::update(float deltaTime)
{
	mesh_.update(deltaTime);
	//çsóÒÇÃê›íË
	mesh_.transform(Getpose());

	position_ += plyaerVector * 0.03f;
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
	//body_->transform(Getpose())->draw();
}

void ArrowAttack::collision()
{
	//Ç‘Ç¬Ç©Ç¡ÇΩÇ©
	Vector3 result;
	//ï«Ç∆Ç‘Ç¬ÇØÇƒÇ©ÇÁ
	if (field(result)) {
		die();
	}

	//è∞Ç∆ÇÃê⁄ínîªíË
	if (floor(result)) {
		die();
	}
}

