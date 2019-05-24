#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationMesh.h"
#include "../World/World.h"
#include "../Actor/ActorSystem/ActorSystem.h"

#include <map>
#include "../Actor/ActorState/ActorStateID.h"
#include "../Actor/ActorParameters.h"
#include "../Actor/ActorState/ActorStateManager.h"

#include "../Actor/ActorCommon/CommonInc.h"
#include "../Actor/ActionPlayerMode/UI/HPUI/ActonPlayerHP.h"


class ActionPlayerActor : public Actor, public ActorSystem {
public:
	ActionPlayerActor(int model, int weapon, IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,9.0f,0.0f }, Matrix::Identity, 10.0f, 4.0f));
	virtual ~ActionPlayerActor() override {}
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//�ǂƏ��̔���
	void collision();
	//�d�͏���
	void gravity_process();
	//���͏��
	void input_information();
	//�ړ�����
	void movement(float speed, Vector2 input);
private:
	using StateMap = std::map<ActorStateID, ActorStateManager>;
	StateMap actionplayerState_;

	ActorStateID mcurrentStateID;

	ActorParameters parameters_;

	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	//���������f��
	int mweapon_;

	ActionPlayerHP mHP;
	ActorPush mAP;

	DrawWeapon mDW;

	Gravity mG;

	MoveInput mI;

	//����`��ʒu
	int mRightweaponPos;
	int mLeftweaponPos;

	Vector3 m_ActionCameraForward;
	Vector3 m_ActionCameraRight;
};