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
#include "../Actor/ActionPlayerMode/UI/HPUI/RedSamuraiHP.h"

#include "../Actor/EnemyCommon/commonInc.h"
#include "../Actor/ActionPlayerMode/UI/Text/RedSamuraiText.h"

class RedSamuraiActor : public Actor, public ActorSystem {
public:
	RedSamuraiActor(int model, int sward, int arrow, int quiver, IWorld* world, const Vector3& position, Matrix & rotation, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,9.0f,0.0f }, Matrix::Identity, 10.0f, 4.0f));
	virtual ~RedSamuraiActor() override {};

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//�v���C���\�̌���
	void getPlayer();
	//�ǂƏ��̔���
	void collision();
	//�U�����邩
	void Attacking();
	//����̈ړ�
	void weapon_transfer();
private:
	using StateMap = std::map<ActorStateID, ActorStateManager>;
	StateMap redsamuraiState_;

	ActorStateID mcurrentStateID;

	ActorParameters parameters_;

	Actor* player_;
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;

	RedSamuraiHP mHP;
	ActorPush mAP;

	DrawWeapon mDW;

	Gravity mG;

	EnemyMove mEV;

	PlayerLook mPL;

	RedSamuraiText mT;

	//���������f��
	int msword_;
	int msword_2;
	int marrow_;
	int mquiver_;
	//����`��ʒu
	int mSwordPos;
	int mArrowPos;
	int mQuiverPos;

	bool mAttackCheck;
	int mAttackTime;

	bool mDeadArelady;

	float mDeadTime;
};
