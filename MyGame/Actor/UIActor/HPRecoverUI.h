#pragma once
#include "../Actor.h"
#include "../../Animation/AnimationMesh.h"

class HPRecoverUI : public Actor {
public:
	HPRecoverUI(int model, IWorld* world, const Vector3& position);

	void initialize() override;

	void update(float deltaTime);

	void draw() const;

private:
	//アニメーションメッシュ
	AnimatedMesh mesh_;
};
