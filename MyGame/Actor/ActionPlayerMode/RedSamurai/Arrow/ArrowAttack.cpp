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
	pos.y = pos.y + 15.0f;//�v���C���[�̐g�����𑫂�

	//�v���C���\�̌����ɖ����������
	rotation_ = Matrix::Invert(Matrix::CreateLookAt(pos, pos + plyaerVector, Vector3::Up) * Matrix::CreateRotationY(180));
}


void ArrowAttack::update(float deltaTime)
{
	mesh_.update(deltaTime);
	//�s��̐ݒ�
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
	//�Ԃ�������
	Vector3 result;
	//�ǂƂԂ��Ă���
	if (field(result)) {
		die();
	}

	//���Ƃ̐ڒn����
	if (floor(result)) {
		die();
	}
}

