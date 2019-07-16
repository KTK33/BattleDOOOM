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

#include "../Effekseer/EffectObj/EffectObj.h"

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
	//パラメータをUIに送る
	void ParamSet();
	//壁と床の判定
	void collision();
	//入力情報
	void input_information();
	//移動処理
	void movement(float speed, Vector2 input);
	//エイム移動処理
	void gun_movement(float speed, Vector2 input);
	//攻撃を受けたとき
	void AttackByHit(int hitVal);
	//無敵時間
	void invincibly(bool check);
	//アイテム処理
	void ItemProcess();
	//回復アイテムを使ったとき
	void UseRecoveryItem(int recovVal);
	//攻撃アイテムを使ったとき
	void UseAttackUpItem(bool upCheck);
private:
	using StateMap = std::map<ActorStateID, ActorStateManager>;
	StateMap shootingplayerState_;

	ActorStateID mcurrentStateID;

	ActorParameters parameters_;

	std::weak_ptr<Actor> m_ui{};
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	//持ち物モデル
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

	EffectObj meff;
	Vector3 meffsize;
	Vector3 meffPos;
};