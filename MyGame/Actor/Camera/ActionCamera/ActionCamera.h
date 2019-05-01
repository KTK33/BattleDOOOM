#pragma once

#include "../Actor/Actor.h"

class ActionCamera : public Actor
{
public:
	ActionCamera(IWorld* world, std::weak_ptr<Actor> m_Player);

	void update(float deltaTime);

	virtual void draw() const override;
	//
	void move(
		const Vector3& rest_position, //�΂˂̐Î~�ʒu
		float stiffness,                //�΂˒萔(�΂˂̋���)
		float friction,                 //���C��
		float mass                      //����
	);

	void PlayerInput(float deltaTime);

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

	int PlayerHeight{ 15 };
};