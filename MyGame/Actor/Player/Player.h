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

	void initialize() override;

	void update(float deltaTime);

	void draw() const;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//�ǂƏ��̔���
	void collision();

	//��Ԃ̍X�V
	void update_state(float deltaTime);
	//��Ԃ̕ύX
	void change_state(PlayerState::State state, int motion);
	void PlayerInput();
	void Idle();
	void IdletoAim();
	void AimtoIdle();
	void IdleAiming();
	void StopGun();
	void Reload();
	void GunPunch();
	void GunMove(float X,float Y);
	void Move(float X, float Y);
	void Gun(PlayerState::State state);
	void Damage();
	void Dead();
	//����̕`��
	void draw_weapon() const;
	//�f�B���C�n
	void Delay();



private:
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
	//���
	PlayerState::State state_;
	PlayerState::State before_state_;
	//��ԃ^�C�}
	float state_timer_;
	//�d��
	const float Gravity{ -0.04f };

	//�c�e��
	int SetRemainGun;
	//�f�B���C�^�C��
	int DelayGunTime;
	bool CheckGun;

	int invinciblyTime;
	bool invinciblyCheck;

	int weaponPos;
};


//���[�V�����ԍ�
enum
{
	MotionPlayerIdel = 0,
	MotionPlayerStopGun = 1,
	MotionPlayerForwardGun = 2,
	MotionPlayerRightGun = 3,
	MotionPlayerLeftGun = 4,
	MotionPlayerBackGun = 5,
	MotionPlayerReload = 6,
	MotionPlayerIdleToAim = 7,
	MotionPlayerAimToIdle = 8,
	MotionPlayerIdle2 = 9,
	MotionPlayerDamageGun = 10,
	MotionPlayerDead = 11,
	MotionPlayerGunPunch = 12,
	MotionPlayerRun = 13,
	MotionPlayerIdleAiming = 14,
	MotionPlayerDamage = 15,
};
