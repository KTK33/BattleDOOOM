#pragma once

#include "../Actor.h"
#include "../../Collision/BoundingCapsule.h"
#include "../../Animation/AnimationMesh.h"
#include "EnemySystem.h"

class DummyEnemyState
{
public:
	enum  State
	{
		IDLE,   //�ҋ@    0
		PUNCH,  //�p���`  1
		ROAR,   //���K    2
		MOVE,   //�ړ�    3
		DAMAGE, //��e    4
		DEAD, //�|���    5
	};
};

class DummyEnemy : public Actor,public EnemySystem {
public:
	DummyEnemy(int model, IWorld* world, const Vector3& position,const Matrix& rotation, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,9.0f,0.0f }, Matrix::Identity, 10.0f, 3.5f));

	void initialize();

	void update(float deltaTime);

	void draw() const;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void* param);

	void collision();
	//��Ԃ̍X�V
	void update_state(float deltaTime);

	void Idle();
	void Roar();
	void Move();
	void Punch();
	void Damage();
	void Dead();

	void hit_player(const Vector3& dir);

	void deadAction();

	//��Ԃ̕ύX
	void change_state(DummyEnemyState::State state, int motion);

	void Action(DummyEnemyState::State state);

	void Delay();

private:
	bool m_EneDead{ false };

	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	//���[�V�����ԍ�
	int motion_;
	//�ړ����x
	const float WalkSpeed{ 0.005f };
	//���
	DummyEnemyState::State state_;
	//��ԃ^�C�}
	float state_timer_;

	int motionNum;

	Actor* player_;

	int invinciblyTime;
	bool invinciblyCheck;

	int maxHp;

	bool roarCheck;

	float AttackDis{ 10.0f };

	bool deadCheck;

};

//���[�V�����ԍ�
enum
{
	MotionDummyIdel = 0,
	MotionDummyPunch = 1,
	MotionDummyRoar = 2,
	MotionDummyMove = 3,
	MotionDummyDamage = 4,
	MotionDummyDead = 5,
};

