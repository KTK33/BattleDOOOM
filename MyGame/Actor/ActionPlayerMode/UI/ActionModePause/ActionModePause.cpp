#include "ActionModePause.h"
#include "../Texture/Sprite.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
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
	if (GameDataManager::getInstance().GetPlayerDead() == false && GameDataManager::getInstance().GetDeadBossEnemy() == false) return;

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM8) || 
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::T))
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
		//�|�[�Y�ł̃L�����Z��
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) || 
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LCTRL))
		{
			PauseDecision = false;
		}
	}
	else
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) || 
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LCTRL))
		{
			world_->SetPauseCheck(false);
		}

		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::UP) || 
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP))
		{
			moveCursor(1);
		}
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::DOWN) || 
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN))
		{
			moveCursor(-1);
		}
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2) || 
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
		{
			PauseDecision = true;
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::PAUSEKETTEI_SE);
		}
	}
}


void ActionModePause::SystemInput()
{
	//if (!areladySystemOpen)
	//{
	//	auto ps = std::make_shared<PauseSystem>(world_);
	//	world_->add_actor(ActorGroup::ItemBoxUI, ps);
	//	ps->setPlayMode(1);
	//	areladySystemOpen = true;
	//}
}