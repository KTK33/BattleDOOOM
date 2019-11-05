#include "ActionModePause.h"
#include "../Texture/Sprite.h"
#include "../Input/InputInfoInc.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Actor/ShootingPlayerMode/UIActor/Pause/PauseSystem.h"
#include "../Sound/Sound.h"

ActionModePause::ActionModePause(IWorld * world) :
	Actor(world, "PauseUI", Vector3::Zero),
	areladySystemOpen{false},
	PauseDecision{false}
{
	initialize();
}

void ActionModePause::initialize()
{
	menuSize_ = 2;
	cursorPos_ = 1;
}

void ActionModePause::update(float deltaTime)
{
	//�v���C���[������ł��邩�{�X������ł�����
	if (GameDataManager::getInstance().GetPlayerDead()
		&& GameDataManager::getInstance().GetDeadBossEnemy()) return;

	if(ButtonStart::GetInstance().TriggerDown())
	{
		PauseDecision = false;

		//�|�[�Y��Ԃ�؂�ւ���
		if (world_->GetPauseCheck() == true){
			world_->SetPauseCheck(false);
		}
		else{
			world_->SetPauseCheck(true);
		}

		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::PAUSEKETTEI_SE);
	}

	if (world_->GetPauseCheck() == true) {
		PlayerInput();
	}
	else
	{
		areladySystemOpen = false;
	}

	if (!PauseDecision)
	{
		areladySystemOpen = false;
	}
}

void ActionModePause::receiveMessage(EventMessage message, void * param)
{}

void ActionModePause::draw() const
{
	if (world_->GetPauseCheck() == true)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::ACTIONPAUSE_BACK, Vector2(0, 0));

		Sprite::GetInstance().Draw(SPRITE_ID::ACTIONPAUSE_OPERATION_UI, Vector2(1050, WINDOW_HEIGHT - 550), Vector2(Sprite::GetInstance().GetSize(SPRITE_ID::ACTIONPAUSE_OPERATION_UI).x / 2, Sprite::GetInstance().GetSize(SPRITE_ID::ACTIONPAUSE_OPERATION_UI).y / 2));
		Sprite::GetInstance().Draw(SPRITE_ID::ACTIONPAUSE_TITLEBACK, Vector2(1050, WINDOW_HEIGHT - 340), Vector2(Sprite::GetInstance().GetSize(SPRITE_ID::ACTIONPAUSE_TITLEBACK).x / 2, Sprite::GetInstance().GetSize(SPRITE_ID::ACTIONPAUSE_TITLEBACK).y / 2));

		//�J�[�\���̏ꏊ�A����ꏊ�ɂ��\�����e�̕ύX
		switch (cursorPos_) {
		case 1:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::ACTIONPAUSE_CURSOR, Vector2(600, WINDOW_HEIGHT - 550));
			if (PauseDecision) Sprite::GetInstance().Draw(SPRITE_ID::ACTIONPAUSE_OPERATION, Vector2(0, 0));
			break;
		case 0:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::ACTIONPAUSE_CURSOR, Vector2(600, WINDOW_HEIGHT - 340));
			if (PauseDecision) world_->SetBackTitleCheck(true);
			break;
		default:break;
		}
	}
}

void ActionModePause::PlayerInput()
{
	if (PauseDecision)
	{
		//��ʂQ�ł̃L�����Z��(�߂�
		if(ButtonA::GetInstance().TriggerDown())
		{
			PauseDecision = false;
		}
	}
	else
	{
		//��ʂP�ł̌���
		if (ButtonB::GetInstance().TriggerDown())
		{
			PauseDecision = true;
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::PAUSEKETTEI_SE);
		}

		//��ʂP�ł̃|�[�Y�I��
		if(ButtonA::GetInstance().TriggerDown())
		{
			world_->SetPauseCheck(false);
		}

		//�J�[�\���㉺
		if(ButtonUp::GetInstance().TriggerDown())
		{
			moveCursor(1);
		}
		if(ButtonDown::GetInstance().TriggerDown())
		{
			moveCursor(-1);
		}
	}
}