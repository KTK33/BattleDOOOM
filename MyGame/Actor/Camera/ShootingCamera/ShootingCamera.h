#pragma once

#include "../../Actor.h"

class ShootingCamera : public Actor
{
public:
	ShootingCamera(IWorld* world, std::weak_ptr<Actor> m_Player);

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	//�΂�
	void move(
		const Vector3& rest_position, //�΂˂̐Î~�ʒu
		float stiffness,                //�΂˒萔(�΂˂̋���)
		float friction,                 //���C��
		float mass                      //����
	);

	//�J�����̐ݒ�
	void CameraSet(float deltaTime);

	//�v���C���[�̓��͏��
	void Aim_Input();

	//�G�C���O
	void Out_Aim();

	//�G�C����
	void In_Aim();

	//�G�C�����̃J��������
	void In_Aim_Rotation();

	//�Q�[���I�����ݒ�
	void PlayerGameFinish();

	//�Q�[���I�[�o�[
	void GameOver();

	//�Q�[���N���A
	void GameClear();


private:
	//�v���C���[�̏�񌟍��p
	Actor* mGetplayer_;

	//�v���C���[�֏��`�B�p
	std::weak_ptr<Actor> mplayer{};

	//�J�����̃^�[�Q�b�g
	Vector3 mtarget_{ 0.0f,0.0f,0.0f };

	//�G�C���̈ʒu
	Vector2 mAimPosMove;

	//
	Vector3 mFinishCamera;
	bool malreadyCreate;
};