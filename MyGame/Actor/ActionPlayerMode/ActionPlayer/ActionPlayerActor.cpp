#include "ActionPlayerActor.h"
#include "ActionStateInc.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Actor/ActionPlayerMode/UI/SceneUI/PlayerDeadUI.h"

ActionPlayerActor::ActionPlayerActor(int model, int weapon, IWorld * world, const Vector3 & position,const IBodyPtr & body):
	Actor(world, "Player", position, body),
	mesh_{ model,weapon },
	mweapon_{ weapon },
	mRightweaponPos{ 15 },
	mLeftweaponPos{ 38 },
	m_ActionCameraForward{ Vector3::Zero },
	m_ActionCameraRight{ Vector3::Zero },
	mDeadArelady{ false }
{
	mcurrentStateID = ActorStateID::ActionPlayerIdel;
	actionplayerState_[ActorStateID::ActionPlayerIdel].add(add_state<ActionPlayerIdle>(world, parameters_));
	actionplayerState_[ActorStateID::ActionPlayerAttack].add(add_state<ActionPlayerAttack>(world, parameters_));
	actionplayerState_[ActorStateID::ActionPlayerAvoidance].add(add_state<ActionPlayerAvoidance>(world, parameters_));
	actionplayerState_[ActorStateID::ActionPlayerAvoidanceAttack].add(add_state<ActionPlayerAvoidanceAttack>(world, parameters_));
	actionplayerState_[ActorStateID::ActionPlayerDead].add(add_state<ActionPlayerDead>(world, parameters_));
	actionplayerState_[mcurrentStateID].initialize();

	initialize();
}

void ActionPlayerActor::initialize()
{
	mesh_.transform(Getpose());
	velocity_ = Vector3::Zero;

	parameters_.Set_Position(position_);
	parameters_.Set_HP(ActionPlayerHPVal);

	parameters_.Set_StateID(mcurrentStateID);
}

void ActionPlayerActor::update(float deltaTime)
{

	prevPosition_ = position_;

	//�Ǐ��Ƃ̂̓����蔻��
	collision();

	//�|�[�Y���͕Ԃ�
	if (world_->GetPauseCheck()) return;

	//�X�e�C�g�N���X�̏����X�V����
	actionplayerState_[mcurrentStateID].update(position_, rotation_, mesh_);

	//�X�e�C�g���ς�����ۂɌĂяo�����
	if (actionplayerState_[mcurrentStateID].Get_NextStateFlag())
	{
		actionplayerState_[mcurrentStateID].NextState(mcurrentStateID);
		actionplayerState_[mcurrentStateID].initialize();
		parameters_.Set_StateID(mcurrentStateID);
		parameters_.Set_Statetimer(0.0f);
	}

	//���S���
	if (parameters_.Get_IsDead())
	{
		//���S���̕`��A�N�^�[����
		if (!mDeadArelady) {
			world_->add_actor(ActorGroup::UI, new_actor<PlayerDeadUI>(world_));
			mDeadArelady = true;
		}
		return;
	}

	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(parameters_.Get_Motion());

	//�d��
	mG.gravity(position_, velocity_, Floorcollide);

	//��Ԏ��Ԃ����Z
	parameters_.Add_Statetime(0.5f);

	//�ړ����͂̏��
	if (parameters_.Get_StateID() == ActorStateID::ActionPlayerIdel || 
		parameters_.Get_StateID() == ActorStateID::ActionPlayerAvoidance)
	{
		input_information();
	}
}

#include "../Texture/Sprite.h"
void ActionPlayerActor::draw() const
{
	mesh_.draw();
	mDW.draw(mweapon_, mRightweaponPos, mesh_);
	mDW.draw(mweapon_, mLeftweaponPos, mesh_);

	mHP.draw(parameters_.Get_HP());
}

void ActionPlayerActor::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER, reinterpret_cast<void*>(&hitdir));
}

void ActionPlayerActor::receiveMessage(EventMessage message, void * param)
{
	//�G�̍U�����󂯂��ۂ�HP�����炷
	if (message == EventMessage::HIT_ENEMY_BULLET)
	{
		parameters_.Red_HP(*static_cast<int*>(param));
	}

	//�G�ƐڐG�����Ƃ��ɏd�Ȃ�Ȃ��悤�ɉ����o��
	if (message == EventMessage::HIT_ENEMY)
	{
		velocity_ = mAP.Hit(*static_cast<Vector3*>(param));
	}

	//�J�����̑O�������擾
	if (message == EventMessage::ACTION_CAMERA_FORWARD)
	{
		m_ActionCameraForward = *static_cast<Vector3*>(param);
	}

	//�J�����̉E�������擾
	if (message == EventMessage::ACTION_CAMERA_RIGHT)
	{
		m_ActionCameraRight = *static_cast<Vector3*>(param);
	}
}

void ActionPlayerActor::collision()
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

void ActionPlayerActor::gravity_process()
{
	//�d�͏���
	//velocity_ = Vector3::Zero;
	velocity_ += Vector3::Up * -gravity;
	position_ += velocity_;

	velocity_ *= 0.8f;
	if (velocity_.Length() < 0.01f) {
		velocity_ = 0.0f;
	}
	if (Floorcollide) gravity = 0.0f;
	else gravity = 9.8f*0.1f;
}

void ActionPlayerActor::input_information()
{
	//�A�C�h����ԂȂ�A�C�h�����[�V�����ɍX�V
	if (parameters_.Get_StateID() == ActorStateID::ActionPlayerIdel) 
	{
		parameters_.Set_Motion(ActionPlayerMotion::MotionPlayerIdel);
	}

	Vector2 input;
	float yaw;

	//���E�㉺����
	mI.Input(input,yaw);
	//���͂������O�Ȃ�΃A�C�h�����
	if (input.x == 0.0f && input.y == 0.0f) return; 
	movement(1.0f, input);
}

void ActionPlayerActor::movement(float speed, Vector2 input)
{
	//�O�㍶�E�ړ�
	velocity_ = Vector3::Zero;
	float forward_speed = 0.0f;
	float side_speed = 0.0f;

	//���͏����ړ��ʂɉ��Z
	side_speed = input.x * speed;
	forward_speed = input.y * speed;

	//�J�����̑O��������O�����Ƃ���
	velocity_ += m_ActionCameraForward * forward_speed;
	velocity_ += m_ActionCameraRight * side_speed;

	//��������x
	static const float mAvoidanceSpeed = 5.0f;

	//����ł̉���
	float DashSpped = 0.0f;

	//�����ԂȂ�
	if (parameters_.Get_StateID() == ActorStateID::ActionPlayerAvoidance)
	{
		velocity_.y = 0.0f;
		velocity_ += velocity_ * mAvoidanceSpeed;
	}
	else
	{
		//�X�e�B�b�N�̓|����Ń��[�V�����ύX
		if (MathHelper::Abs(input.x) < 0.8f || MathHelper::Abs(input.y) < 0.8f) {
			parameters_.Set_Motion(ActionPlayerMotion::MotionPlayerWalk);
		}
		else {
			parameters_.Set_Motion(ActionPlayerMotion::MotionPlayerRun);
			DashSpped = 0.5f;
		}
	}

	//�i��ł�������Ɍ���
	Vector3 angle = m_ActionCameraForward * input.y + m_ActionCameraRight * input.x;
	angle.y = 0.0f;
	Matrix to_Target_rotate = Matrix::CreateLookAt(position_, position_ + angle.Normalize(), Vector3::Up);
	rotation_ = Matrix::Lerp(rotation_, Matrix::Invert(to_Target_rotate) * Matrix::CreateRotationY(180), 0.1f);

	position_ += velocity_ * (1.0f + DashSpped);
}