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

class RedSamuraiActor : public Actor, public ActorSystem {
public:
	RedSamuraiActor(int model, int sward, int arrow, int quiver, IWorld* world, const Vector3& position, Matrix & rotation, std::weak_ptr<Actor> ui, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,9.0f,0.0f }, Matrix::Identity, 10.0f, 4.0f));
	virtual ~RedSamuraiActor() override {};

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//プレイヤ―の検索
	void getPlayer();
	//壁と床の判定
	void collision();
	//重力処理
	void gravity_process();
	//プレイヤー向き
	Matrix PlayerLook();
	//武器の描画
	void draw_weapon() const;
	//武器の移動
	void weapon_transfer();
	//接触
	void Hit(const Vector3& dir);
private:
	std::weak_ptr<Actor> m_ui{};
	IBodyPtr Initbody;
	Actor* player_;
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	//持ち物モデル
	int sword_;
	int arrow_;
	int quiver_;

	//移動速度
	const float WalkSpeed{ 0.25f };
	//武器描画位置
	int mSwordPos;
	int mArrowPos;
	int mQuiverPos;

	using StateMap = std::map<ActorStateID, ActorStateManager>;
	StateMap redsamuraiState_;

	ActorStateID mcurrentStateID;

	ActorParameters parameters_;
};
