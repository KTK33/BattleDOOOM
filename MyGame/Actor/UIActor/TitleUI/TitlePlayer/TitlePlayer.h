#pragma once

#include "../Actor/Actor.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationMesh.h"
#include "../Actor/ActorSystem/ActorSystem.h"

class TitlePlayer : public Actor,public ActorSystem  {
public:
	TitlePlayer(int model, int weapon, IWorld* world, const Vector3& position);

	void initialize() override;

	void update(float deltaTime);

	void draw() const;

	//武器の描画
	void draw_weapon() const;

private:
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	int motion_;
	//持ち物モデル
	int weapon_;

	int Timer;
};