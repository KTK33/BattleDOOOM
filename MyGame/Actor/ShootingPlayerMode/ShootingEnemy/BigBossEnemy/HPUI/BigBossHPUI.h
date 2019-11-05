#pragma once
#include "../Math/MathH.h"
#include "../Actor/Actor.h"

//大ボスのHPUIクラス
class BigBossHPUI : public Actor
{
public:
	BigBossHPUI(IWorld* world);
	virtual ~BigBossHPUI() override {}

	virtual void draw() const override;

	virtual void receiveMessage(EventMessage message, void * param) override;

private:
	int mhp;
};