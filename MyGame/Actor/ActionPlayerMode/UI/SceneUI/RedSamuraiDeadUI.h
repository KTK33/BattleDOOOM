#pragma once
#include "../Actor/Actor.h"
#include "../Scene/Menu.h"
#include "SceneCommon/SceneCommon.h"
#include "../Effekseer/EffectObj/EffectObj.h"

class RedSamuraiDeadUI : public Actor,public Menu {
public:
	RedSamuraiDeadUI(IWorld* world);

	virtual void update(float deltaTime) override;

	virtual void draw() const;

private:
	void input();

private:
	bool mAlready;

	SceneCommon mSC;

	EffectObj meff;

	int mTime;

	Vector3 mRedPos;
};