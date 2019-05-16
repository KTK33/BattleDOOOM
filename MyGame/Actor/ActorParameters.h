#pragma once

#include <string>

#include "../Math/MathH.h"
#include "../Collision/Base/IBodyPtr.h"

#include "ActorState/ActorStateID.h"

//�A�N�^�[�p�����[�^�����N���X
class ActorParameters
{
public:
	ActorParameters();

	//���O�擾
	std::string Get_Name()const;
	//���O�ݒ�
	void Set_Name(std::string lname);

	//�|�W�V�����擾
	Vector3 Get_Position()const;
	//�|�W�V�����ݒ�
	void Set_Position(Vector3 lposition);

	//�ړ��ʎ擾
	Vector3 Get_Velocity()const;
	//�ړ��ʐݒ�
	void Set_Velocity(Vector3 lvelocity);

	//1�t���[���O�̃|�W�V�����擾
	Vector3 Get_PrevPosition()const;
	//1�t���[���O�̃|�W�V�����ݒ�
	void Set_PrevPosition(Vector3 lprevposition);

	//��]�擾
	Matrix Get_Rotation()const;
	//��]�ݒ�
	void Set_Rotation(Matrix lmatrix);

	//����̎擾
	IBodyPtr Get_Body()const;
	//����̐ݒ�
	void Set_Body(IBodyPtr lbody);

	//���S����擾
	bool Get_IsDead()const;
	//���S����ݒ�
	void Set_IsDead(bool lisFlag); 

	//���[�V�����̎擾
	int Get_Motion() const;
	//���[�V�����̐ݒ�
	void Set_Motion(int num);

	//��Ԃ̎擾
	ActorStateID Get_StateID()const;
	//��Ԃ̐ݒ�
	void Set_StateID(ActorStateID lstateID);

	//�O��Ԃ̎擾
	ActorStateID Get_PrevStateID()const;
	//�O��Ԃ̐ݒ�
	void Set_PreveStateID(ActorStateID lprevstateID);

	//�X�e�C�g�̎��Ԏ擾
	float Get_Statetimer() const;
	//�X�e�C�g�̎��Ԑݒ�
	void Set_Statetimer(float ltime);
	//�X�e�C�g�̎��ԉ��Z
	void Add_Statetime(float atime);

	//HP�̎擾
	int Get_HP() const;
	//HP�̐ݒ�
	void Set_HP(int lhp);
	//HP�̌��Z
	void Red_HP(int rhp);


private:
	std::string mname{};

	Vector3 mposition{ Vector3::Zero };
	Vector3 mvelocity{ Vector3::Zero };
	Vector3 mprevposition{ Vector3::Zero };

	Matrix mrotation{ Matrix::Identity };

	// �Փ˔���
	IBodyPtr mbody_{nullptr};

	bool misDead{ false };

	int mmotion{ 0 };

	ActorStateID mstate{ ActorStateID::NONE };
	ActorStateID mprevstate{ ActorStateID::NONE };

	float mstatetimer{ 0.0f };

	int mhp{ 0 };
};