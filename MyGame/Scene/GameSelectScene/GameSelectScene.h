#pragma once
#include"../Scene.h"
#include"../World/World.h"
#include "../Scene/Menu.h"

//���\�[�X�ǂݍ��ݐ�p�V�[��
class GameSelectScene :public Scene ,public Menu{
public:

	GameSelectScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	World world_;
};