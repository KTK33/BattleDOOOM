#pragma once
#include"../Scene.h"
#include"../World/World.h"

//���\�[�X�ǂݍ��ݐ�p�V�[��
class GameTitleScene :public Scene{
public:

	GameTitleScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	World world_;
};