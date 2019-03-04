#include "PauseSystem.h"
#include "../../Texture/Sprite.h"
#include "../../Input/GamePad.h"
#include "../../Scene/GameData/GameDataManager.h"

PauseSystem::PauseSystem(IWorld * world):
	Actor(world,"PauseSytem",Vector3::Zero)
{
	menuSize_ = 3;
	menuSize_2 = 9;
	cursorPos_ = 0;
	cursorPos_2 = 5;

	bgmval = GameDataManager::getInstance().GetBGMVAL();
	seval = GameDataManager::getInstance().GetSEVAL();
	aimval = GameDataManager::getInstance().GetAIMSPD();

}

void PauseSystem::initialize()
{
}

void PauseSystem::update(float deltaTime)
{
	PlayerInput();
}

void PauseSystem::draw() const
{
	switch (cursorPos_)
	{
		case 0:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAMS, Vector2(1350, WINDOW_HEIGHT -650.0f));
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 500.0f));
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 350.0f));
			break;
		case 1:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 650.0f));
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAMS, Vector2(1350, WINDOW_HEIGHT - 500.0f));
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 350.0f));
			break;
		case 2:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 650.0f));
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 500.0f));
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAMS, Vector2(1350, WINDOW_HEIGHT - 350.0f));

			break;
	default:
		break;
	}

	Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_CURSOR, Vector2(802.f + GameDataManager::getInstance().GetBGMVAL() * 100.f, WINDOW_HEIGHT - 650.0f));
	Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_CURSOR, Vector2(802.f + GameDataManager::getInstance().GetSEVAL() * 100.f, WINDOW_HEIGHT - 500.0f));
	Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_CURSOR, Vector2(802.f + GameDataManager::getInstance().GetAIMSPD() * 100.f, WINDOW_HEIGHT - 350.0f));

	//DrawFormatString(1000, 700, GetColor(255, 0, 0), "%i", GameDataManager::getInstance().GetBGMVAL());
	DrawFormatString(1000, 600, GetColor(255, 0, 0), "%i", GameDataManager::getInstance().GetSEVAL());
	DrawFormatString(1000, 500, GetColor(255, 0, 0), "%i", GameDataManager::getInstance().GetAIMSPD());

}

void PauseSystem::receiveMessage(EventMessage message, void * param)
{
}

void PauseSystem::PlayerInput()
{
	switch (cursorPos_)
	{
	case 0:
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::RIGHT))
		{
			if (bgmval < 10) bgmval = bgmval + 1;
		}
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::LEFT))
		{
			if (bgmval > 1) bgmval = bgmval - 1;
		}
		GameDataManager::getInstance().SetBGMVAL(bgmval);
		break;
	case 1:
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::RIGHT))
		{
			if (seval < 10) seval = seval + 1;
		}
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::LEFT))
		{
			if (seval > 1) seval = seval - 1;
		}
		GameDataManager::getInstance().SetSEVAL(seval);
		break;
	case 2:
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::RIGHT))
		{
			if(aimval < 10) aimval = aimval + 1;
		}
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::LEFT))
		{
			if(aimval > 1) aimval = aimval - 1;
		}
		GameDataManager::getInstance().SetAIMSPD(aimval);
		break;
	default:
		break;
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::UP))
	{
		moveCursor(-1);

	}
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::DOWN))
	{
		moveCursor(1);
	}
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
	{
		die();
	}
}
