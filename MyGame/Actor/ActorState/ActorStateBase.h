#pragma once

#include "../Math/Vector3.h"

#include "ActorStateID.h"
#include "../ActorParameters.h"
#include "../Animation/AnimationMesh.h"


class IWorld;
class ActorParameters;

//�A�N�^�[��ԃN���X���
class ActorStateBase
{
public:
	ActorStateBase() = default;

	//���z�֐��@��ԏ�����
	virtual void Stateinitialize();

	//���z�֐���ԍX�V
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation,AnimatedMesh & lmesh);

	//���̏�ԂɈڍs����t���O���擾
	bool Get_NextStateFlag() const;

	//���̏�Ԃ��擾
	ActorStateID Get_NextStateID() const;

	ActorStateBase(const ActorStateBase& other) = delete;
	ActorStateBase& operator=(const ActorStateBase& other) = delete;

protected:
	IWorld* world_{ nullptr };
	ActorParameters* parameters_{ nullptr };

	bool mNextStateFlag;
	ActorStateID mNextStateID;
};