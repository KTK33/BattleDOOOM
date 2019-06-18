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
#include "../Actor/EnemyCommon/commonInc.h"

#include "HPUI/BossHPUI.h"

class BossEnemyActor : public Actor, public ActorSystem {
public:
	BossEnemyActor(int model, IWorld* world, const Vector3& position,const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,10.0f,0.0f }, Matrix::Identity, 10.0f, 6.0f));
	virtual ~BossEnemyActor() override {}
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//�ǂƏ��̔���
	void collision();
	//�v���C���[�̌���
	void getPlayer();
	//�U�����邩
	void Attacking();
	//�e�ɓ���������
	void BulletHit(int damage);
	//���G����
	void invincibly(bool check);
private:
	using StateMap = std::map<ActorStateID, ActorStateManager>;
	StateMap bossenemyState_;

	ActorStateID mcurrentStateID;

	ActorParameters parameters_;

	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;

	ActorPush mAP;

	BossHP mBH;

	Gravity mG;

	EnemyMove mEV;

	PlayerLook mPL;

	Actor* player_;

	Vector3 HSPos{ 0.0f,15.0f,0.0f };

	bool mroarCheck;

	float mAttackDis{ 10.0f };

	int mDamageParam;

	bool mAttackCheck;
	int mAttackTime;
};