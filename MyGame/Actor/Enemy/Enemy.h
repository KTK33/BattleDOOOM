#ifndef ENEMY_H_
#define ENEMY_H_

#include "../../Mesh/SkeletalMesh.h"
#include "../../Mesh/StaticMesh.h"
#include "../../Graphics/Graphics3D.h"
#include "../../Input/GamePad.h"
#include "../../Math/MathH.h"
#include "../Player/Player.h"
#include "../../Animation/Animation.h"
#include "../../Animation/AnimationMesh.h"
#include "../Actor.h"

//�G�̃��[�V�����ԍ�
enum
{
	EnemyMotionIdle = 0,
	EnemyMotionWalk = 1,
	EnemyMotionTurnLeft = 2,
	EnemyMotionTurnRight = 3,
	EnemyMotionDamage = 4,
	EnemyMotionAttack = 5,
	EnemyMotionDead = 6
};

//�G�N���X
class Enemy : public Actor {
public:
	enum class State
	{
		Idle,     //�A�C�h�����
		Walk,     //����
		Turn,     //�U�����
		Damage,   //�_���[�W
		Attack    //�U��
	};

public:
	//�R���X�g���N�^
	Enemy(int model, const Vector3& position,IWorld& world);
	//�X�V
	virtual void update(float delta_time);
	//�`��
	virtual void draw() const;
	//�Փˏ���
	virtual void react(Actor& other) override;
	//�s��̎擾
	//Matrix pose() const;

private:
	//��Ԃ̍X�V
	void update_state(float delta_time);
	//��Ԃ̕ύX
	void change_state(State state, int motion);
	//�A�C�h�����
	void idle(float delta_time);
	//�ړ���
	void walk(float delta_time);
	//�U�������
	void turn(float delta_time);
	//�U����
	void attack(float delta_time);
	//�_���[�W��
	void damage(float delta_time);
	//�U���������
	bool is_turn() const;
	//�U������
	bool is_attack() const;
	//�ړ�����
	bool is_walk() const;
	//�^�[�Q�b�g�����̊p�x�����߂�
	float target_angle() const;
	//�^�[�Q�b�g�̋��������߂�
	float target_distance() const;

private:
	////����
	//Matrix rotation_;
	////���W
	//Vector3 position_;
	////�ړ���
	//Vector3 velocity_;
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	//���[�V�����ԍ�
	int motion_;
	//���
	State state_;
	//��ԃ^�C�}
	float state_timer_;
	//�v���C���[
	Actor* player_;
	
	int timer_;

	//�U���������
	const float TurnDistance{ 15.0f };
	//�U���͈�
	const float AttackDistance{ 12.0f };
	//�ړ��X�s�[�h
	const float WalkSpeed{ 0.25f };
	//�U������p�x
	const float TurnAngle{ 2.5f };
};


#endif // !ENEMY_H_

