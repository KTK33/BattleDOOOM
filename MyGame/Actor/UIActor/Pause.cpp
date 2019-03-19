#include "Pause.h"
#include "../../Texture/Sprite.h"
#include "../../Input/GamePad.h"
#include "../../Scene/GameData/GameDataManager.h"
#include "PauseSystem.h"

PauseUI::PauseUI(IWorld * world):
	Actor(world,"PauseUI",Vector3::Zero)
{
	menuSize_ = 4;
	animeTime = 0;
	cursorPos_ = 3;

	UISize[3] = 1.2f;
	UISize[2] = 1;
	UISize[1] = 1;
	UISize[0] = 1;

	PauseDecision = false;

	areladySystemOpen = false;

}

void PauseUI::initialize()
{
}

void PauseUI::update(float deltaTime)
{
	if (GameDataManager::getInstance().GetPlayerDead() == false)
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM8)) {
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

		//Sprite::GetInstance().DrawPart(SPRITE_ID::PAUSECIRCLE, Vector2(1000, (float)WINDOW_HEIGHT - (250 + cursorPos_ * 160)), anime * 150, 0, 150, 150);

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
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
		{
			PauseDecision = false;
			GameDataManager::getInstance().SetItemBoXOpen(false);
		}
	}
	else
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
		{
			world_->SetPauseCheck(false);
		}

		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::UP))
		{
			moveCursor(1);
			//animeTime = 0;
			//anime = 0;
		}
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::DOWN))
		{
			moveCursor(-1);
			//animeTime = 0;
			//anime = 0;
		}
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2))
		{
			PauseDecision = true;
		}

	}


}

void PauseUI::Pause()
{
	//animeTime++;
	//if (animeTime % 5 == 0)
	//{
	//	if (anime < 5)
	//	{
	//		anime += 1;
	//	}
	//}

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
		world_->add_actor(ActorGroup::ItemBoxUI, new_actor<PauseSystem>(world_));
		areladySystemOpen = true;
	}
}
