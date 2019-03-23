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
		FIRE_BEFO,
		FIRE,
		FIRE_AFTE,
		DAMAGE,
		DEAD, 
	};
};

class BossEnemy : public Actor,public EnemySystem  {
public:
	BossEnemy(int model, IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,9.0f,0.0f }, Matrix::Identity, 12.0f, 4.0f));

	void initialize();

	void update(float deltaTime);

	void draw() const;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void* param);

	void collision();

	//��Ԃ̍X�V
	void update_state(float deltaTime);

	void Idle();
	void MoveWalk();
	void MoveRun();
	void Punch();
	void AttackFireBefo();
	void AttackFire();
	void AttackFireAfte();
	void Damage();
	void Dead();

	//��Ԃ̕ύX
	void change_state(BossEnemyState::State state, int motion);

	void hit_player(const Vector3& dir);

	void deadAction();

	void Delay();

private:
	AnimatedMesh mesh_;

	//���[�V�����ԍ�
	int motion_;
	//�ړ����x
	const float WalkSpeed{ 0.005f };
	float WalkVal;
	//���
	BossEnemyState::State state_;
	//��ԃ^�C�}
	float state_timer_;


	int invinciblyTime;
	bool invinciblyCheck;

	Actor* player_;

	float AttackDis{ 15.0f };

	bool Ikari;

	std::weak_ptr<Actor> m_ui{};

	bool FireCheck;
	int FireCount;


};


//���[�V�����ԍ�
enum
{
	MotionBossIdel = 0,
	MotionBossWalk,
	MotionBossRun,
	MotionBossPunch,
	MotionBossPunch2,
	MotionBossDamage,
	MotionBossDead,
	MotionBossFireBefo,
	MotionBossFireAfte,
};
