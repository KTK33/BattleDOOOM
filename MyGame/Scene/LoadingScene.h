#pragma once
#include"Scene.h"

//���\�[�X�ǂݍ��ݐ�p�V�[��
class LoadingScene :public Scene {
public:
	LoadingScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	//�摜�̓ǂݍ���
	void LoadSprite();
	//���f���̓ǂݍ���
	void LoadModel();
	//�F�X�ǂݍ���
	void LoadAny();
	//�V�F�[�_�[�̓ǂݍ���
	void LoadShader();
	//�摜�f�[�^�̔j��
	void DeleteRes();
};