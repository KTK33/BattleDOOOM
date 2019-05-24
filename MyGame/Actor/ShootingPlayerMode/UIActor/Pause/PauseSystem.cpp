#include "PauseSystem.h"
#include "../Texture/Sprite.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Sound/Sound.h"

PauseSystem::PauseSystem(IWorld * world):
	Actor(world,"PauseSytem",Vector3::Zero)
{
	initialize();
}

void PauseSystem::initialize()
{
	menuSize_ = 3;
	menuSize_2 = 9;
	cursorPos_ = 0;
	cursorPos_2 = 5;

	bgmval = GameDataManager::getInstance().GetBGMVAL() * 10;
	seval = GameDataManager::getInstance().GetSEVAL() * 10;
	aimval = GameDataManager::getInstance().GetAIMSPD();
}

void PauseSystem::update(float deltaTime)
{
	PlayerInput();

	Sound::GetInstance().SetAllBGMVolume(GameDataManager::getInstance().GetBGMVAL());
	Sound::GetInstance().SetAllSEVolume(GameDataManager::getInstance().GetSEVAL());
}

void PauseSystem::draw() const
{
	switch (cursorPos_)
	{
		case 0:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAMS, Vector2(1350, WINDOW_HEIGHT -650.0f));
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 500.0f));
			if(modenum == 0) Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 350.0f));
			break;
		case 1:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 650.0f));
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAMS, Vector2(1350, WINDOW_HEIGHT - 500.0f));
			if (modenum == 0) Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 350.0f));
			break;
		case 2:
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 650.0f));
			Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAM, Vector2(1350, WINDOW_HEIGHT - 500.0f));
			if (modenum == 0) Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_FREAMS, Vector2(1350, WINDOW_HEIGHT - 350.0f));

			break;
	default:
		break;
	}

	Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_CURSOR, Vector2(802.f + bgmval * 100.f, WINDOW_HEIGHT - 650.0f));
	Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_CURSOR, Vector2(802.f + seval * 100.f, WINDOW_HEIGHT - 500.0f));
	if (modenum == 0) Sprite::GetInstance().DrawSetCenter(SPRITE_ID::PAUSESYSTEM_CURSOR, Vector2(802.f + aimval * 100.f, WINDOW_HEIGHT - 350.0f));
}

void PauseSystem::receiveMessage(EventMessage message, void * param)
{
}

void PauseSystem::PlayerInput()
{
	switch (cursorPos_)
	{
	case 0:
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::RIGHT) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT))
		{
			if (bgmval < 10) bgmval = bgmval + 1;
		}
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::LEFT) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT))
		{
			if (bgmval > 1) bgmval = bgmval - 1;
		}
		GameDataManager::getInstance().SetBGMVAL(static_cast<int>(bgmval));
		break;
	case 1:
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::RIGHT) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT))
		{
			if (seval < 10) seval = seval + 1;
		}
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::LEFT) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT))
		{
			if (seval > 1) seval = seval - 1;
		}
		GameDataManager::getInstance().SetSEVAL(static_cast<int>(seval));
		break;
	case 2:
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::RIGHT) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT))
		{
			if(aimval < 10) aimval = aimval + 1;
		}
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::LEFT) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT))
		{
			if(aimval > 1) aimval = aimval - 1;
		}
		GameDataManager::getInstance().SetAIMSPD(static_cast<int>(aimval));
		break;
	default:
		break;
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::UP) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP))
	{
		moveCursor(-1);

	}
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::DOWN) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN))
	{
		moveCursor(1);
	}
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LCTRL) ||
		GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM8) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::T))
	{
		die();
	}
}

void PauseSystem::setPlayMode(int num)
{
	modenum = num;
}
