#pragma once

#include "../Actor.h"
#include "../../Collision/BoundingCapsule.h"
#include "../../Mesh/SkeletalMesh.h"
#include "../../Mesh/StaticMesh.h"
#include "../../Animation/Animation.h"
#include "../../Animation/AnimationMesh.h"
#include "PlayerState.h"
#include "../../World/World.h"
#include "../ActorSystem.h"

class Player : public Actor,public ActorSystem{
public:
	Player(int model,int weapon,IWorld* world, const Vector3& position, std::weak_ptr<Actor> ui,const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{0.0f,9.0f,0.0f},Matrix::Identity,10.0f,4.0f));

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
	void Reload();
	void GunPunch();
	void GunMove(float X,float Y);
	void Move(float X, float Y);
	void Gun();
	void PlayerGunFire();
	void JumpChacker(PlayerState::State state);
	void Jump();
	void Damage();
	void Dead();
	void Tyohatu();
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
	PlayerState::State state_;
	PlayerState::State before_state_;
	//��ԃ^�C�}
	float state_timer_;
	//�d��
	const float Gravity{ -0.04f };

	//�c�e��(�Z�b�g����Ă���)
	int SetRemainGun;
	//���ݎ����Ă���e��
	int HaveGun;
	//�f�B���C�^�C��
	int DelayGunTime;

	int invinciblyTime;
	bool invinciblyCheck;

	int weaponPos;

	Vector3 AimPos;
	Vector3 InitAimPos;

	int RecoverItemCount;
	int AttackItemCount;

	int alreadyItem;

	bool DeadCheck;

	bool GunPossible;

	int AttackParam;
	bool AttackUpCheck;
	int AttackUpTime;
};
