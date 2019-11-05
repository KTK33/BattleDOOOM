#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Animation/AnimationMesh.h"

//�A�N�V�������[�h�̃^�[�Q�b�g�J����
class TargetCameraManager : public Actor {
public:
	TargetCameraManager(IWorld* world, std::weak_ptr<Actor> player, std::weak_ptr<Actor> camera);
	virtual ~TargetCameraManager() override {}

	virtual void update(float deltaTime) override;

private:
	std::weak_ptr<Actor> mPlayer{};
	std::weak_ptr<Actor> mCamera{};

	bool mTargetCamera;
};
