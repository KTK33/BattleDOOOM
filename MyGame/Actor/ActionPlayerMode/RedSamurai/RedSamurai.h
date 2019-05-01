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
	RedSamurai(int model, int weapon, IWorld* world, const Vector3& position, std::weak_ptr<Actor> ui, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,9.0f,0.0f }, Matrix::Identity, 10.0f, 4.0f));

	void initialize() override;

	void update(float deltaTime);

	void draw() const;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//�ǂƏ��̔���
	void collision();

	//��Ԃ̕ύX
	void change_state(RedSamuraiState::State state, int motion);
	void Idle();
	void Motion(float deltaTime);
	//����̕`��
	void draw_weapon() const;
	//�f�B���C�n
	void Delay();

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
	RedSamuraiState::State state_;
	RedSamuraiState::State before_state_;
	//��ԃ^�C�}
	float state_timer_;
	//�d��
	const float Gravity{ -0.04f };

	//���G����
	int invinciblyTime;
	bool invinciblyCheck;

	//����`��ʒu
	int mweaponPos;

	bool DeadCheck;
};
