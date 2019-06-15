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

class BigBossEnemyActor : public Actor, public ActorSystem {
public:
	BigBossEnemyActor(int model, IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,13.0f,0.0f }, Matrix::Identity, 17.0f, 5.0f));
	virtual ~BigBossEnemyActor() override {}
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//壁と床の判定
	void collision();
	//プレイヤーの検索
	void getPlayer();
	//プレイヤーの方を向く
	void LookPlayer();
	//攻撃するか
	void Attacking();
	//弾に当たったら
	void BulletHit(int damage);
private:
	using StateMap = std::map<ActorStateID, ActorStateManager>;
	StateMap bigbossenemyState_;

	ActorStateID mcurrentStateID;

	ActorParameters parameters_;

	//アニメーションメッシュ
	AnimatedMesh mesh_;

	ActorPush mAP;

	Gravity mG;

	EnemyMove mEV;

	PlayerLook mPL;

	Actor* player_;

	int mDamageParam;

	int mAttackTime;
	int mAttackTimeInit{ 60 };

	EnemyMove mEM;

	bool mAttack;
};