#pragma once
#include "../Actor/Actor.h"

//�^�C�g���w�i
class TitleBack : public Actor {
public:
	TitleBack(IWorld* world);
	virtual ~TitleBack()override{}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:
	int TitleBackAlpha;
};