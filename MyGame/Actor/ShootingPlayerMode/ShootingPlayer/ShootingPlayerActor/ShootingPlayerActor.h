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

#include "../Actor/ShootingPlayerMode/UIActor/ParamUI/ParamUI.h"

#include "../Actor/ActorCommon/CommonInc.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/PlayerMove/PlayerMove.h"

class ShootingPlayerActor : public Actor, public ActorSystem {
public:
	ShootingPlayerActor(int model, int weapon, IWorld* world, const Vector3& position, std::weak_ptr<Actor> ui, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,9.0f,0.0f }, Matrix::Identity, 10.0f, 4.0f));
	virtual ~ShootingPlayerActor() override {}
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//�p�����[�^��UI�ɑ���
	void ParamSet();
	//�ǂƏ��̔���
	void collision();
	//���͏��
	void input_information();
	//�ړ�����
	void movement(float speed, Vector2 input);
	//�G�C���ړ�����
	void gun_movement(float speed, Vector2 input);
	//���G����
	void invincibly(bool check);
private:
	using StateMap = std::map<ActorStateID, ActorStateManager>;
	StateMap shootingplayerState_;

	ActorStateID mcurrentStateID;

	ActorParameters parameters_;

	std::weak_ptr<Actor> m_ui{};
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	//���������f��
	int mweapon_;

	ParamUI mParamUI;

	ActorPush mAP;

	DrawWeapon mDW;

	Gravity mG;

	PlayerMove mMV;

	MoveInput mI;

	int mweaponPos;

	Vector3 mInitAimPos;

	int mRecoverItemCount;
	int mAttackItemCount;

	int mAttackParam;
	bool mAttackUpCheck;
	int mAttackUpTime;
};