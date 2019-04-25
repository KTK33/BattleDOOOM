#pragma once
#include"../Scene.h"
#include"../World/World.h"
#include "../Menu.h"

//���\�[�X�ǂݍ��ݐ�p�V�[��
class ActionPlayScene :public Scene, public Menu {
public:

	ActionPlayScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	World world_;
};