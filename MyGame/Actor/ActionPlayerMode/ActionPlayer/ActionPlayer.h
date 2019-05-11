#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationMesh.h"
#include "ActionPlayerState.h"
#include "../World/World.h"
#include "../Actor/ActorSystem/ActorSystem.h"

class ActionPlayer : public Actor, public ActorSystem {
public:
	ActionPlayer(int model, int weapon, IWorld* world, const Vector3& position, std::weak_ptr<Actor> ui, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,9.0f,0.0f }, Matrix::Identity, 10.0f, 4.0f));
	virtual ~ActionPlayer() override {}
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//�ǂƏ��̔���
	void collision();

	//��Ԃ̕ύX
	void change_state(ActionPlayerState::State state, int motion);
	void Idle();
	void Move(Vector2 input);
	void Movement(float spped, Vector2 input);
	void Attack();
	void AttackSystem();
	void AttackAvoidanceSystem();
	void AttackCollision(int deadTime,int attackParam,Vector3 spot,float len,float rad);
	void Motion(float deltaTime);
	//����̕`��
	void draw_weapon() const;

	void Hit(Vector3& dir);
private:
	std::weak_ptr<Actor> m_ui{};
	IBodyPtr Initbody;
	//World world__;
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	//���[�V�����ԍ�
	int motion_;
	int before_motion_;
	//���������f��
	int weapon_;
	//�ړ����x
	const float WalkSpeed{ 0.25f };

	//���,
	ActionPlayerState::State state_;
	ActionPlayerState::State before_state_;
	//��ԃ^�C�}
	float state_timer_;
	//�d��
	const float Gravity{ -0.04f };

	//����`��ʒu
	int mRightweaponPos;
	int mLeftweaponPos;

	bool DeadCheck;

	Vector3 m_ActionCameraForward;
	Vector3 m_ActionCameraRight;

	int mAttackCount;
	bool mAttackcheck;
	bool mweaponalready;
};
