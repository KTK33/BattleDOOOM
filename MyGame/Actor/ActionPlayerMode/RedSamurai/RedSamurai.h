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
	//�v���C���\��[��
	void getPlayer();
	//�ǂƏ��̔���
	void collision();
	//��Ԃ̕ύX
	void change_state(RedSamuraiState::State state, int motion);
	void AttackTimeCheck(float deltaTime);
	void AttackSystem();
	void AttackBehavior();
	void AttackCollision(int deadTime, int attackParam, Vector3 spot, float len, float rad);
	Matrix PlayerLook();
	float GetPlayerDistance();
	void Movement(float deltaTime);
	void Motion(float deltaTime);
	//����̕`��
	void draw_weapon() const;

	void Hit(Vector3& dir);
private:
	std::weak_ptr<Actor> m_ui{};
	IBodyPtr Initbody;
	Actor* player_;
	//World world__;
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	//���[�V�����ԍ�
	int motion_;
	int before_motion_;
	//���������f��
	int sword_;
	int arrow_;
	int quiver_;

	//�ړ����x
	const float WalkSpeed{ 0.25f };

	//���,
	RedSamuraiState::State state_;
	RedSamuraiState::State before_state_;
	//��ԃ^�C�}
	float state_timer_;
	//�d��
	const float Gravity{ -0.04f };

	//����`��ʒu
	int mSwordPos;
	int mArrowPos;
	int mQuiverPos;

	bool DeadCheck;

	int mAttackTime;
	int mAttackTimeInit;

	int mAttacktype;
};
