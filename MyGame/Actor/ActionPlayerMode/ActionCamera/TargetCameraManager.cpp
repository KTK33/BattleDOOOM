#include "TargetCameraManager.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
#include "../Input/InputInfoInc.h"
#include "../Scene/GameData/GameDataManager.h"

TargetCameraManager::TargetCameraManager(IWorld * world, std::weak_ptr<Actor> player, std::weak_ptr<Actor> camera):
	Actor(world, "TargetCameraManager", Vector3::Zero),
	mPlayer{player},
	mCamera{camera},
	mTargetCamera{false}
{
}

void TargetCameraManager::update(float deltaTime)
{
	if (GameDataManager::getInstance().GetDeadBossEnemy() ||
		GameDataManager::getInstance().GetPlayerDead()){
		mTargetCamera = false;
	}

	//�G�̌���
	auto enemy_ = world_->find_actor(ActorGroup::Enemy, "RedSamurai").get();
	if (enemy_ == nullptr) return;

	//�J�������ɓG���f���Ă��邩�ǂ���
	if (!CheckCameraViewClip_Dir(enemy_->Getposition()))
	{
		if(ButtonR3::GetInstance().TriggerDown())
		{
			if (world_->GetPauseCheck() == true) return;//�|�[�Y���͖���
			mTargetCamera = !mTargetCamera;
		}

		//�v���C���[�ƃJ�����ɏ��𑗐M
		mPlayer.lock()->receiveMessage(EventMessage::TARGET_CAMERA, reinterpret_cast<void*>(&mTargetCamera));
		mCamera.lock()->receiveMessage(EventMessage::TARGET_CAMERA, reinterpret_cast<void*>(&mTargetCamera));
	}
}
