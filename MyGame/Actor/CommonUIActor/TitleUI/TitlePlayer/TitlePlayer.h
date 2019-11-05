#pragma once

#include "../Actor/Actor.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationMesh.h"
#include "../Actor/ActorSystem/ActorSystem.h"
#include "../Actor/ActorCommon/DrawWeapon/DrawWeapon.h"

//�^�C�g�����̃v���C���[�i�w�����j�A�N�^�[
class TitlePlayer : public Actor,public ActorSystem  {
public:
	TitlePlayer(int model, int weapon, IWorld* world, const Vector3& position);
	virtual ~TitlePlayer() override{}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	int mmotion_;
	//���������f��
	int mweapon_;

	int mTimer;

	DrawWeapon mDW;
};