#include "TitleAnyUI.h"
#include "../../../Texture/Sprite.h"
#include "../../../Scene/GameData/GameDataManager.h"
#include "../../../Input/GamePad.h"
#include "../../../Input/Keyboard.h"
#include "TitleBack.h"
#include "../FadeUI.h"
#include "../Sound/Sound.h"

TitleAnyUI::TitleAnyUI(IWorld * world) :
	Actor(world, "TitleAnuUI", Vector3::Zero),
	NameSize{ Vector2::One * 3 },
	NameBackSize{ Vector2::Zero },
	NameBackAlpha{ 255 },
	NameAngle{ MathHelper::Pi / 2 },
	PressStartAlpha{ 255 },
	StartDecision{ false },
	PSAlphaCheck{ false },
	PSCount{ 0 },
	PSAlphaSpeed{ 10 },
	alreadyTitleBack{ false },
	TitleBackWhiteAlpha{0},
	TitleBackWhiteCheck{false},
	alreadyFadeCheck{false},
	NameBackSize2{0,0}
{
}

void TitleAnyUI::initialize()
{
}

void TitleAnyUI::update(float deltaTime)
{
	NameSize.x = max(NameSize.x-0.1f, 1);
	NameSize.y = max(NameSize.y-0.1f, 1);

	NameAngle = max(NameAngle - 0.075f, 0);

	if (NameSize.x == 1)
	{
		if (!StartDecision)
		{
			NameBackAlpha = max(NameBackAlpha - 5, 0);
			NameBackSize.x = max(NameBackSize.x + 0.005f, 2);
			NameBackSize.y = max(NameBackSize.y + 0.005f, 2);
		}
	}

	if (NameBackAlpha == 0)
	{
		if (!Sound::GetInstance().IsPlayBGM())
		{
			Sound::GetInstance().PlayBGM(BGM_ID::TITLE_BGM, DX_PLAYTYPE_LOOP);
		}
		if (!alreadyTitleBack)
		{
			world_->add_actor(ActorGroup::UIBefore, new_actor<TitleBack>(world_));
			alreadyTitleBack = true;
		}
		if (GamePad::GetInstance().AnyTriggerDown() || Keyboard::GetInstance().AnyTriggerDown())
		{
			StartDecision = true;
			Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::TITLEKETTEI_SE);
		}
	}

	if (StartDecision)
	{
		if (PSAlphaCheck)
		{
			PressStartAlpha = min(PressStartAlpha + PSAlphaSpeed, 255);
			if (PressStartAlpha == 255) PSAlphaCheck = false;
		}
		else
		{
			if (PSCount == 0) PSAlphaSpeed = 50;
			if (PSCount == 2) PSAlphaSpeed = 10;
			PressStartAlpha = max(PressStartAlpha - PSAlphaSpeed, 0);
			if (PressStartAlpha == 0)
			{
				PSCount = PSCount + 1;
				if (PSCount == 3)
				{
					TitleBackWhiteCheck = true;
				}
				else {
					PSAlphaCheck = true;
				}
			}
		}
		
		if (TitleBackWhiteCheck)
		{
			NameBackSize2.x = max(NameBackSize2.x + 0.05f, 2);
			NameBackSize2.y = max(NameBackSize2.y + 0.05f, 2);
			TitleBackWhiteAlpha = min(TitleBackWhiteAlpha + 20, 255);
			if (TitleBackWhiteAlpha == 255)
			{
				TitleBackWhiteCheck = false;
			}
		}
		else if(PSCount >= 3)
		{
			TitleBackWhiteAlpha = max(TitleBackWhiteAlpha - 50, -500);

			if (TitleBackWhiteAlpha == -500)
			{
				if (!alreadyFadeCheck)
				{
					world_->add_actor(ActorGroup::Fade, new_actor<FadeUI>(world_, 0,1));
					alreadyFadeCheck = true;
				}
			}
		}
	}
}

void TitleAnyUI::receiveMessage(EventMessage message, void * param)
{
}

void TitleAnyUI::draw() const
{
	Vector2 NameSpriteSize = Sprite::GetInstance().GetSize(SPRITE_ID::TITLENAME);
	Sprite::GetInstance().Draw(SPRITE_ID::TITLENAME, Vector2((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT - 900), NameSpriteSize/2,NameSize,NameAngle);

	if (NameSize.x == 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, NameBackAlpha);
		Sprite::GetInstance().Draw(SPRITE_ID::TITLENAMEBACK, Vector2((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT - 900), NameSpriteSize / 2, NameBackSize);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (NameBackAlpha == 0 && PSCount < 3)
	{
		Vector2 PressStartSize = Sprite::GetInstance().GetSize(SPRITE_ID::TITLEPRESS_START);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, PressStartAlpha);
		Sprite::GetInstance().Draw(SPRITE_ID::TITLEPRESS_START, Vector2((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT - 200), PressStartSize / 2);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (TitleBackWhiteCheck)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, TitleBackWhiteAlpha);
		Sprite::GetInstance().Draw(SPRITE_ID::TITLEBACKWHITE, Vector2(0, 0));
		Sprite::GetInstance().Draw(SPRITE_ID::TITLENAMEBACK, Vector2((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT - 900), NameSpriteSize / 2, NameBackSize2);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}