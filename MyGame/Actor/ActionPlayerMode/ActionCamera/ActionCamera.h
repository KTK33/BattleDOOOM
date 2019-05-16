#pragma once

#include "../Actor/Actor.h"

class ActionCamera : public Actor
{
public:
	ActionCamera(IWorld* world, std::weak_ptr<Actor> m_Player);
	virtual ~ActionCamera()override{}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	void PlayerInput(float deltaTime);

	virtual void receiveMessage(EventMessage message, void * param) override;

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

	bool mTargetCamera;
};