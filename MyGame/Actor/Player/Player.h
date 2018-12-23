#pragma once

#include "../Actor.h"
#include "../../Collision/BoundingCapsule.h"
#include "../../Mesh/SkeletalMesh.h"
#include "../../Mesh/StaticMesh.h"
#include "../../Animation/Animation.h"
#include "../../Animation/AnimationMesh.h"
#include "PlayerState.h"
#include "../../World/World.h"

class Player : public Actor {
public:
	Player(int model,int weapon,IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{0.0f,5.0f,0.0f},Matrix::Identity,15.0f,4.0f));

	virtual void initialize() override;

	void update(float deltaTime);

	void draw() const;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//��Ԃ̍X�V
	void update_state(float delta_time);
	//��Ԃ̕ύX
	void change_state(PlayerState::State state, int motion);
	//�ړ�����
	void move(float delta_time);
	//�p���`
	void punch(float delta_time);
	//�L�b�N
	void kick(float delta_time);
	//��
	void sword(float delta_time);
	//�e
	void gun(float delta_time);
	//�_���[�W��
	void damage(float delta_time);
	//�W�����v��
	void jump(float delta_time);
	//����̕`��
	void draw_weapon() const;



private:
	//World world__;
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	//���[�V�����ԍ�
	int motion_;
	//���������f��
	int weapon_;
	//�ړ����x
	const float WalkSpeed{ 0.25f };
	//���
	PlayerState::State state_;
	//��ԃ^�C�}
	float state_timer_;
	//�d��
	const float Gravity{ -0.04f };

	//�c�e��
	int RemainGun;

	//�f�B���C�^�C��
	int DelayGunTime;

};


//���[�V�����ԍ�
enum
{
	MotionIdel = 0,
	MotionForwardWalk = 1,
	MotionBackarWalk = 1,
	MotionLeftWalk = 1,
	MotionRightWalk = 1,
	MotionPunch = 4,
	MotionKick = 5,
	MotionGun = 7,
	MotionSword = 6,
	MotionDamage = 8,
	MotionJump = 3
};
