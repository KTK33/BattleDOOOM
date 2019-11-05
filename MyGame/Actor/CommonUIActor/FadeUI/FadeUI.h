#pragma once
#include "../Actor/Actor.h"

//�t�F�[�hUI�N���X
class FadeUI : public Actor {
public:
	//�R���X�g���N�^�i�O�F�t�F�[�h�C���@�P�F�t�F�[�h�A�E�g�j
	FadeUI(IWorld* world,int FadeCheck,int SceneNum);
	virtual ~FadeUI()override {}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:
	int FadeAlpha;
	int m_FadeCheck;
	int m_SceneNum;
};