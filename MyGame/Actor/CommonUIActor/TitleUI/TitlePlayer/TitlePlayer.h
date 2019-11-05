#pragma once

#include "../Actor/Actor.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationMesh.h"
#include "../Actor/ActorSystem/ActorSystem.h"
#include "../Actor/ActorCommon/DrawWeapon/DrawWeapon.h"

//タイトル時のプレイヤー（学生服）アクター
class TitlePlayer : public Actor,public ActorSystem  {
public:
	TitlePlayer(int model, int weapon, IWorld* world, const Vector3& position);
	virtual ~TitlePlayer() override{}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	int mmotion_;
	//持ち物モデル
	int mweapon_;

	int mTimer;

	DrawWeapon mDW;
};