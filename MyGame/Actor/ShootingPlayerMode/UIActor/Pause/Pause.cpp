#include "Pause.h"
#include "../Texture/Sprite.h"
#include "../Input/InputInfoInc.h"
#include "../Scene/GameData/GameDataManager.h"
#include "PauseSystem.h"
#include "../Sound/Sound.h"

PauseUI::PauseUI(IWorld * world):
	Actor(world,"PauseUI",Vector3::Zero)
{
	initialize();
}

void PauseUI::initialize()
{
	menuSize_ = 4;
	cursorPos_ = 3;

	UISize[3] = 1.2f;
	UISize[2] = 1;
	UISize[1] = 1;
	UISize[0] = 1;

	PauseDecision = false;

	areladySystemOpen = false;
}

void PauseUI::update(float deltaTime)
{
	if (GameDataManager::getInstance().GetPlayerDead() == false && GameDataManager::getInstance().GetDeadBossEnemy() == false)
	{
		if(ButtonStart::GetInstance().TriggerDown())
		{
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::PAUSEKETTEI_SE);
			PauseDecision = false;
			if (world_->GetPauseCheck() == true)
			{
				world_->SetPauseCheck(false);
			}
			else
			{
				world_->SetPauseCheck(true);
			}
		}
	}
	
	if (world_->GetPauseCheck() == true){
		PlayerInput();
		Pause();
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

void PauseUI::receiveMessage(EventMessage message, void * param)
{
}

void PauseUI::draw() const
{
	if (world_->GetPauseCheck() == true)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::PAUSEBACK, Vector2(0, 0));

		Sprite::GetInstance().Draw(SPRITE_ID::PAUSEITEM, Vector2(1050, WINDOW_HEIGHT- 660),Vector2(Sprite::GetInstance().GetSize(SPRITE_ID::PAUSEITEM).x/2, Sprite::GetInstance().GetSize(SPRITE_ID::PAUSEITEM).y/2),Vector2(UISize[0],UISize[0]));
		Sprite::GetInstance().Draw(SPRITE_ID::PAUSEOPERATION, Vector2(1050, WINDOW_HEIGHT - 490), Vector2(Sprite::GetInstance().GetSize(SPRITE_ID::PAUSEOPERATION).x / 2, Sprite::GetInstance().GetSize(SPRITE_ID::PAUSEOPERATION).y / 2), Vector2(UISize[1], UISize[1]));
		Sprite::GetInstance().Draw(SPRITE_ID::PAUSESYSTEM, Vector2(1050, WINDOW_HEIGHT - 340), Vector2(Sprite::GetInstance().GetSize(SPRITE_ID::PAUSESYSTEM).x / 2, Sprite::GetInstance().GetSize(SPRITE_ID::PAUSESYSTEM).y / 2), Vector2(UISize[2], UISize[2]));
		Sprite::GetInstance().Draw(SPRITE_ID::PAUSETITLE, Vector2(1050, WINDOW_HEIGHT - 180), Vector2(Sprite::GetInstance().GetSize(SPRITE_ID::PAUSETITLE).x / 2, Sprite::GetInstance().GetSize(SPRITE_ID::PAUSETITLE).y / 2), Vector2(UISize[3], UISize[3]));

		switch (cursorPos_){
		case 3:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSEITEM_DESCRIPTION, Vector2(1050, WINDOW_HEIGHT - 50.0f));
			if (PauseDecision) Sprite::GetInstance().Draw(SPRITE_ID::ITEM, Vector2(0, 0));
			break;
		case 2:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSEOPERATION_DESCRIPTION, Vector2(1050, WINDOW_HEIGHT - 50.0f));
			if (PauseDecision) Sprite::GetInstance().Draw(SPRITE_ID::OPERATION, Vector2(0, 0));
			break;
		case 1:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_DESCRIPTION, Vector2(1050, WINDOW_HEIGHT - 50.0f));
			if (PauseDecision) Sprite::GetInstance().Draw(SPRITE_ID::SYSTEM, Vector2(0, 0));
			break;
		case 0:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSETITLE_DESCRIPTION, Vector2(1050, WINDOW_HEIGHT - 50.0f));
			if (PauseDecision) world_->SetBackTitleCheck(true);
			break;
		default:break;
		}
	}
}

void PauseUI::PlayerInput()
{
	if (PauseDecision)
	{
		//画面２でのキャンセル(戻る)
		if(ButtonA::GetInstance().TriggerDown())
		{
			PauseDecision = false;
			GameDataManager::getInstance().SetItemBoXOpen(false);
		}
	}
	else
	{
		//ポーズ中の決定(画面１)
		if (ButtonB::GetInstance().TriggerDown())
		{
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::PAUSEKETTEI_SE);
			PauseDecision = true;
		}

		//ポーズを閉じる
		if(ButtonA::GetInstance().TriggerDown())
		{
			world_->SetPauseCheck(false);
		}

		//カーソルの上下
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

void PauseUI::Pause()
{
	//画面１での選んでるものの文字の大きさが大きくなる
	switch (cursorPos_){
	case 0:	
		UISize[3] = 1.25f;
		UISize[2] = 1;
		UISize[1] = 1;
		UISize[0] = 1;

		break;
	case 1:
		UISize[3] = 1;
		UISize[2] = 1.25f;
		UISize[1] = 1;
		UISize[0] = 1;
		if(PauseDecision)SystemInput();
		break;
	case 2:
		UISize[3] = 1;
		UISize[2] = 1;
		UISize[1] = 1.25f;
		UISize[0] = 1;
		break;
	case 3:
		UISize[3] = 1;
		UISize[2] = 1;
		UISize[1] = 1;
		UISize[0] = 1.25f;
		break;

	default:break;
	}
}

void PauseUI::SystemInput()
{
	if (!areladySystemOpen)
	{
		auto ps = std::make_shared<PauseSystem>(world_);
		world_->add_actor(ActorGroup::ItemBoxUI, ps);
		ps->setPlayMode(0);
		areladySystemOpen = true;
	}
}
