#pragma once
#include"../Scene.h"

//���\�[�X�ǂݍ��ݐ�p�V�[��
class ActionModeLoadingScene :public Scene {
public:
	ActionModeLoadingScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	//���f���̓ǂݍ���
	void LoadModel();
	//�F�X�ǂݍ���
	void LoadAny();
	//�V�F�[�_�[�̓ǂݍ���
	void LoadShader();
	//�T�E���h�̓ǂݍ���
	void LoadSound();
	//�摜�̓ǂݍ���
	void LoadSprite();

private:
	int Countres{ 0 };
};