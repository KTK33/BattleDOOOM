#include "RedSamuraiActor.h"
#include "../../ActorGroup.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
#include "../Texture/Sprite.h"
#include "../Scene/GameData/GameDataManager.h"
#include "RedSamuraiMotionNum.h"
#include "Arrow/ArrowAttack.h"
#include "../Actor/EnemyAttackCollison/EnemyAttackCollison.h"

#include "State/RedSamuraiIdle.h"
#include "State/RedSamuraiWalk.h"
#include "State/RedSamuraiAttack.h"
#include "State/RedSamuraiDead.h"

RedSamuraiActor::RedSamuraiActor(int model, int sward, int arrow, int quiver, IWorld * world, const Vector3 & position, Matrix & rotation,const IBodyPtr & body):
Actor(world, "RedSamurai", position, body),
	player_{ nullptr },
	mesh_{ model,sward },
	msword_{ sward },
	marrow_{ arrow },
	mquiver_{ quiver },
	mSwordPos{ 38 },
	mArrowPos{ 76 },
	mQuiverPos{ 82 }
{
	rotation_ = rotation;

	mcurrentStateID = ActorStateID::RedSamuraiIdel;
	redsamuraiState_[ActorStateID::RedSamuraiIdel].add(add_state<RedSamuraiIdle>(world, parameters_));
	redsamuraiState_[ActorStateID::RedSamuraiWalk].add(add_state<RedSamuraiWaik>(world, parameters_));
	redsamuraiState_[ActorStateID::RedSamuraiAttack].add(add_state<RedSamuraiAttack>(world, parameters_));
	redsamuraiState_[ActorStateID::RedSamuraiDead].add(add_state<RedSamuraiDead>(world, parameters_));
	redsamuraiState_[mcurrentStateID].initialize();

	initialize();
}

void RedSamuraiActor::initialize()
{
	mesh_.transform(Getpose());
	velocity_ = Vector3::Zero;

	parameters_.Set_Position(position_);
	parameters_.Set_HP(PlayerHP);
}

void RedSamuraiActor::update(float deltaTime)
{
	//�X�e�C�g�N���X�̏����X�V����
	redsamuraiState_[mcurrentStateID].update(position_,rotation_,mesh_);

	//�X�e�C�g���ς�����ۂɌĂяo�����
	if (redsamuraiState_[mcurrentStateID].Get_NextStateFlag())
	{
		redsamuraiState_[mcurrentStateID].NextState(mcurrentStateID);
		redsamuraiState_[mcurrentStateID].initialize();
		parameters_.Set_StateID(mcurrentStateID);
	}

	//�Ǐ��Ƃ̂̓����蔻��
	collision();

	//�|�[�Y���͕Ԃ�
	if (world_->GetPauseCheck() == true) return;

	//����ł�����
	if (parameters_.Get_IsDead() == true)
	{
		GameDataManager::getInstance().SetDeadBossEnemy(true);
		return;
	}

	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(parameters_.Get_Motion());

	//�|�W�V�����̍X�V
	position_ = parameters_.Get_Position();

	//�d��
	mG.gravity(position_, velocity_, Floorcollide);

	//�v���C���[�̎擾
	getPlayer();

	//�U����ԈȊO�̎��Ƀv���C���[�̕����Ɍ���
	if(mcurrentStateID != ActorStateID::RedSamuraiAttack) rotation_ *= PlayerLook();

	//��Ԏ��Ԃ����Z
	parameters_.Add_Statetime(0.5f);

	//����̈ʒu
	weapon_transfer();
}

void RedSamuraiActor::draw() const
{
	mesh_.draw();
	mHP.draw(parameters_.Get_HP());
	mDW.draw(msword_, mSwordPos, mesh_);
	mDW.draw(marrow_, mArrowPos, mesh_);
	mDW.draw(mquiver_, mQuiverPos, mesh_);


	SetFontSize(32);
	DrawFormatString(1400, 450, GetColor(255, 0, 0), "%f", position_.x);
	DrawFormatString(1400, 550, GetColor(255, 0, 0), "%f", position_.y);
	DrawFormatString(1400, 650, GetColor(255, 0, 0), "%f", position_.z);
	DrawFormatString(1400, 700, GetColor(255, 0, 0), "%i", mSwordPos);
	DrawFormatString(1400, 750, GetColor(255, 0, 0), "%f", Vector3::Distance(position_, player_->Getposition()));
	SetFontSize(16);

}

void RedSamuraiActor::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (int*)&hitdir);
}

void RedSamuraiActor::receiveMessage(EventMessage message, void * param)
{
	//�v���C���[�̍U�����󂯂��ۂ�HP�����炷
	if (message == EventMessage::HIT_PLAYER_PUNCH)
	{
		parameters_.Red_HP(*static_cast<int*>(param));
	}

	//�v���C���[�ƐڐG�����Ƃ��ɏd�Ȃ�Ȃ��悤�ɉ����o��
	if (message == EventMessage::HIT_PLAYER)
	{
		velocity_ = mAP.Hit(*static_cast<Vector3*>(param));
	}
}

void RedSamuraiActor::getPlayer()
{
	//�v���C���[�̎擾
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void RedSamuraiActor::collision()
{
	//�Ԃ�������
	Vector3 result;
	//�ǂƂԂ��Ă���
	if (field(result)) {
		position_.x = result.x;
		position_.z = result.z;
		Stagecollide = true;
	}
	else {
		Stagecollide = false;
	}

	//���Ƃ̐ڒn����
	if (floor(result)) {
		Floorcollide = true;
		position_ = result + rotation_.Up()*(body_->length()*0.7f + body_->radius()*0.7f);
	}
	else {
		Floorcollide = false;
	}
}

Matrix RedSamuraiActor::PlayerLook()
{
	//�^�[�Q�b�g�����ɏ�����������ς��� Clamp�Ŗ������p�x(-TurnAngle�`TurnAngle)����
	const auto angle = MathHelper::Clamp(PlayerDirection(player_, position_, rotation_), -2.5f, 2.5f);
	return  Matrix::CreateRotationY(angle);
}

void RedSamuraiActor::weapon_transfer()
{
	mArrowPos = 76;
	if (world_->find_actor(ActorGroup::EnemyBullet, "ArrowAttack") == NULL)return;
	mArrowPos = 38;
}