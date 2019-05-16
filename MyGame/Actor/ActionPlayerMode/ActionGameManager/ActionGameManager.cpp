#include "ActionGameManager.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"

ActionGameManager::ActionGameManager(IWorld * world, std::weak_ptr<Actor> player, std::weak_ptr<Actor> camera):
	Actor(world, "RedSamurai", Vector3::Zero),
	mPlayer{player},
	mCamera{camera},
	mTargetCamera{false}
{
}

void ActionGameManager::update(float deltaTime)
{
	//�G�̌���
	auto enemy_ = world_->find_actor(ActorGroup::Enemy, "RedSamurai").get();
	if (enemy_ == nullptr) return;

	//�J�������ɓG���f���Ă��邩�ǂ���
	if (!CheckCameraViewClip_Dir(enemy_->Getposition()))
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM10) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LCTRL))
		{
			if (world_->GetPauseCheck() == true) return;//�|�[�Y���͖���
			mTargetCamera = !mTargetCamera;
		}

		//�v���C���[�ƃJ�����ɏ��𑗐M
		mPlayer.lock()->receiveMessage(EventMessage::TARGET_CAMERA, reinterpret_cast<void*>(&mTargetCamera));
		mCamera.lock()->receiveMessage(EventMessage::TARGET_CAMERA, reinterpret_cast<void*>(&mTargetCamera));
	}
}
