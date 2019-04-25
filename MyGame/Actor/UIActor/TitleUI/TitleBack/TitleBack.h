#pragma once
#include "../Actor/Actor.h"

class TitleBack : public Actor {
public:
	TitleBack(IWorld* world);
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const;

private:
	int TitleBackAlpha;
};