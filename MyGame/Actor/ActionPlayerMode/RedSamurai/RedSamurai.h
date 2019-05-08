#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationMesh.h"
#include "RedSamuraiState.h"
#include "../World/World.h"
#include "../Actor/ActorSystem/ActorSystem.h"

class RedSamurai : public Actor, public ActorSystem {
public:
	RedSamurai(int model, int sward, int arrow, int quiver, IWorld* world, const Vector3& position, Matrix & rotation, std::weak_ptr<Actor> ui, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,9.0f,0.0f }, Matrix::Identity, 10.0f, 4.0f));

	void initialize() override;

	void update(float deltaTime);

	void draw() const;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//プレイヤ―野啓作
	void getPlayer();
	//壁と床の判定
	void collision();
	//状態の変更
	void change_state(RedSamuraiState::State state, int motion);
	void AttackTimeCheck(float deltaTime);
	void AttackSystem();
	void AttackBehavior();
	void AttackCollision(int deadTime, int attackParam, Vector3 spot, float len, float rad);
	Matrix PlayerLook();
	float GetPlayerDistance();
	void Movement(float deltaTime);
	void Motion(float deltaTime);
	//武器の描画
	void draw_weapon() const;

	void Hit(Vector3& dir);
private:
	std::weak_ptr<Actor> m_ui{};
	IBodyPtr Initbody;
	Actor* player_;
	//World world__;
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	//モーション番号
	int motion_;
	int before_motion_;
	//持ち物モデル
	int sword_;
	int arrow_;
	int quiver_;

	//移動速度
	const float WalkSpeed{ 0.25f };

	//状態,
	RedSamuraiState::State state_;
	RedSamuraiState::State before_state_;
	//状態タイマ
	float state_timer_;
	//重力
	const float Gravity{ -0.04f };

	//武器描画位置
	int mSwordPos;
	int mArrowPos;
	int mQuiverPos;

	bool DeadCheck;

	int mAttackTime;
	int mAttackTimeInit;

	int mAttacktype;
};
