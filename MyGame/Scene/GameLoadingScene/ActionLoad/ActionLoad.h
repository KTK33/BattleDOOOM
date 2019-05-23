#pragma once
#include "../Scene/Scene.h"
#include "../DrawLoadScene/DrawLoadScene.h"

//���\�[�X�ǂݍ��ݐ�p�V�[��
class ActionLoad :public Scene {
public:
	ActionLoad();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	//���f���̓ǂݍ���
	void LoadModel();
	//�T�E���h�̓ǂݍ���
	void LoadSound();
	//�摜�̓ǂݍ���
	void LoadSprite();

private:
	int Countres{ 0 };

	DrawLoadScene mDL;
};