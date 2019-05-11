#pragma once

#include "../Actor/Actor.h"
#include "../Animation/AnimationMesh.h"

class TitleBullet : public Actor
{
public:
	TitleBullet(int model, IWorld* world, const Vector3& position,Vector3 move);
	virtual ~TitleBullet()override{}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

private:
	AnimatedMesh mesh_;

	Vector3 MovePos;

	int Timer;
};