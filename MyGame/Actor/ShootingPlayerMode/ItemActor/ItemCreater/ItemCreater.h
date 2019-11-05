#pragma once
#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Animation/AnimationMesh.h"

//アイテム生成クラス
class ItemCreater : public Actor {
public:
	ItemCreater(IWorld* world, const Vector3& position);
	virtual ~ItemCreater() override{}

	virtual void update(float deltaTime)override;
};
