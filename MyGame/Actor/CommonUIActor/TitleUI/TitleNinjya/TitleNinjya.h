#pragma once

#include "../Actor/Actor.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationMesh.h"
#include "../Actor/ActorCommon/DrawWeapon/DrawWeapon.h"

class TitleNinjya : public Actor{
public:
	TitleNinjya(int model, int weapon, IWorld* world, const Vector3& position);
	virtual ~TitleNinjya() override {}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	int mmotion_;
	//���������f��
	int mweapon_;

	DrawWeapon mDW;
};