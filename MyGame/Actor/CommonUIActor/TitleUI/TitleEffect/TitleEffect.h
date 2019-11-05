#pragma once

#include "../Actor/Actor.h"
#include "../Effekseer/EffectObj/EffectObj.h"

//タイトルエフェクト
class TitleEffect : public Actor {
public:
	TitleEffect(IWorld* world);
	virtual ~TitleEffect() override {}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:

	EffectObj meff;

	int mTimer;

	Vector3 mEffectPos;
};