#pragma once
#include "../Actor/Actor.h"

class TitleAnyUI : public Actor {
public:
	TitleAnyUI(IWorld* world);
	virtual ~TitleAnyUI() override{}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:
	Vector2 NameSize;
	float NameAngle;
	Vector2 NameBackSize;
	int NameBackAlpha;
	bool StartDecision;
	int PressStartAlpha;
	bool PSAlphaCheck;
	int PSCount;
	int PSAlphaSpeed;
	bool alreadyTitleBack;
	int TitleBackWhiteAlpha;
	bool TitleBackWhiteCheck;
	bool alreadyFadeCheck;
	Vector2 NameBackSize2;
};