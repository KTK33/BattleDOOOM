#pragma once
#include "../Actor/Actor.h"
#include "../Scene/Menu.h"
#include "SceneCommon/SceneCommon.h"
#include "../Effekseer/EffectObj/EffectObj.h"

//�A�N�V�������[�h�̃v���C���[���S��UI�N���X
class PlayerDeadUI : public Actor,public Menu {
public:
	PlayerDeadUI(IWorld* world);

	virtual void update(float deltaTime) override;

	virtual void draw() const;

private:
	void input();

private:
	bool mAlready;

	SceneCommon mSC;

	EffectObj meff;

	int mTime;

	Vector3 mPlayerPos;
};