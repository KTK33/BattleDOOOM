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

	//����̕`��
	void draw_weapon() const;

private:
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	int motion_;
	//���������f��
	int weapon_;

	int Timer;
};