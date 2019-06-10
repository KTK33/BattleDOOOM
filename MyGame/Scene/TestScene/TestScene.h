#pragma once
#include "../SceneInc.h"

#include "../Effekseer/EffekseerEffect/EffekseerEffect.h"
#include "../Effekseer/EffectObj/EffectObj.h"


//���\�[�X�ǂݍ��ݐ�p�V�[��
class TestScene :public Scene{
public:

	TestScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	World world_;

	EffectObj eff_;
};