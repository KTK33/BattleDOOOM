#pragma once
#include "../Actor/Actor.h"

class FadeUI : public Actor {
public:
	FadeUI(IWorld* world,int FadeCheck,int SceneNum);
	virtual ~FadeUI()override {}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:
	int FadeAlpha;
	int m_FadeCheck;
	int m_SceneNum;
};