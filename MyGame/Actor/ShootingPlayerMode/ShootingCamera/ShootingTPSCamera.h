#pragma once

#include "../Actor/Actor.h"
#include "../Actor/ShootingPlayerMode/UIActor/SightUI/SightUI.h"

//�V���[�e�B���O���[�h��TPS�J����
class ShootingTPSCamera : public Actor
{
public:
	ShootingTPSCamera(IWorld* world, std::weak_ptr<Actor> m_Player);
	virtual ~ShootingTPSCamera()override {}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	void PlayerInput(float deltaTime);

	virtual void receiveMessage(EventMessage message, void * param) override;

private:
	//�Q�[���I�����ݒ�
	void PlayerGameFinish();

	//���̃V�[���̃^�C�v
	void NextSceneType(int type);

private:
	Actor* player_;
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	std::weak_ptr<Actor> m_player{};

	//�^�[�Q�b�g����̃I�t�Z�b�g
	Vector3 mOffset;
	//�J�����̏�����x�N�g��
	Vector3 mUp;
	//�s�b�`�̊p���x
	float mPitchSpeed;
	//���[�̊p���x
	float mYawSpeed;
	//�O����
	Vector3 mForward;

	//�v���C���[�̍���
	int PlayerHeight{ 15 };

	SightUI mSU;

	//
	Vector3 mFinishCamera;
	bool malreadyCreate;
};