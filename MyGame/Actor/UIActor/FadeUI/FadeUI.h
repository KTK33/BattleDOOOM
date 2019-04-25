#pragma once
#include "../Actor/Actor.h"

class FadeUI : public Actor {
public:
	FadeUI(IWorld* world,int FadeCheck,int SceneNum);
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const;

private:
	int FadeAlpha;
	int m_FadeCheck;
	int m_SceneNum;
};