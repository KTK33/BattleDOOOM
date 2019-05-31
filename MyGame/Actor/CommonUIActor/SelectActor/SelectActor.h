#pragma once
#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationMesh.h"
#include "../World/World.h"
#include "../Actor/ActorCommon/DrawWeapon/DrawWeapon.h"

class SelectActor : public Actor {
public:
	SelectActor(int model1, int model2,int weapon1,int weapon2,IWorld* world);
	virtual ~SelectActor()override {}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void receiveMessage(EventMessage message, void * param) override;

private:
	//アニメーションメッシュ
	AnimatedMesh mesh1, mesh2;
	int mmotion1;
	int mmotion2;

	//持ち物モデル
	int mweapon1;
	int mweapon2;

	DrawWeapon mDW;

	int mNum;

	int mweaponPos1;
	int mweaponPos2_;
	int mweaponPos2_1;
};