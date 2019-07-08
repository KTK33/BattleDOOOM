#pragma once

#include "../Actor/Actor.h"
#include "../Actor/ShootingPlayerMode/UIActor/SightUI/SightUI.h"

class ShootingTPSCamera : public Actor
{
public:
	ShootingTPSCamera(IWorld* world, std::weak_ptr<Actor> m_Player);
	virtual ~ShootingTPSCamera()override {}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	void PlayerInput(float deltaTime);

	virtual void receiveMessage(EventMessage message, void * param) override;

	//�Q�[���I�����ݒ�
	void PlayerGameFinish();

	//���̃V�[���̃^�C�v
	void NextSceneType(int type);

private:
	Actor* player_;
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	Vector2 m_FarPoint{ 30.f,20.f };

	std::weak_ptr<Actor> m_player{};

	//�^�[�Q�b�g����̃I�t�Z�b�g
	Vector3 m_Offset;
	//�J�����̏�����x�N�g��
	Vector3 m_Up;
	//�s�b�`�̊p���x
	float m_PitchSpeed;
	//���[�̊p���x
	float m_YawSpeed;

	//�v���C���[�̍���
	int PlayerHeight{ 15 };

	SightUI mSU;

	//
	Vector3 mFinishCamera;
	bool malreadyCreate;
};