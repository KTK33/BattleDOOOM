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
	Actor* mplayer_;
	//
	Vector3 mtarget_{ 0.0f,0.0f,0.0f };

	Vector2 mFarPoint{ 30.f,20.f };

	float mangle{ 0 };

	Vector2 mAimPosMove;

	std::weak_ptr<Actor> mplayer{};

	Vector3 mDeadCamera{ 20,20,20 };
	bool malreadyGO;
};