#pragma once

#include "../Actor.h"
#include "../../Collision/BoundingCapsule.h"
#include "../../Animation/AnimationMesh.h"
#include "EnemySystem.h"

class BossEnemyState
{
public:
	enum  State
	{
		IDLE,
		WALK,
		RUN,
		PUNCH,
		DAMAGE,
		DEAD, 
	};
};

class BossEnemy : public Actor,public EnemySystem  {
public:
	BossEnemy(int model, IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,5.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));

	void initialize();

	void update(float deltaTime);

	void draw() const;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void* param);

	//状態の更新
	void update_state(float deltaTime);

	void Idle();
	void MoveWalk();
	void MoveRun();
	void Punch();
	void Damage();
	void Dead();

	//状態の変更
	void change_state(BossEnemyState::State state, int motion);

	void hit_player(const Vector3& dir);

	void deadAction();

	void Delay();

private:
	AnimatedMesh mesh_;

	//モーション番号
	int motion_;
	//移動速度
	const float WalkSpeed{ 0.005f };
	//状態
	BossEnemyState::State state_;
	//状態タイマ
	float state_timer_;


	int invinciblyTime;
	bool invinciblyCheck;

	Actor* player_;

	float AttackDis{ 15.0f };

};


//モーション番号
enum
{
	MotionBossIdel = 0,
	MotionBossWalk = 1,
	MotionBossRun = 2,
	MotionBossPunch = 3,
	MotionBossPunch2 = 4,
	MotionBossDamage = 5,
	MotionBossDead = 6,
};
