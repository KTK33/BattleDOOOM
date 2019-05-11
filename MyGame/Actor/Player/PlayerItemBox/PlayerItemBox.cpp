#include "PlayerItemBox.h"
#include "../Texture/Sprite.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
#include "../Scene/GameData/GameDataManager.h"

PlayerItemBox::PlayerItemBox(IWorld * world,int HPItem,int AttackItem, std::weak_ptr<Actor> player):
	Actor(world,"PlayerBox",Vector3::Zero),
	countHPrecoverItem{ HPItem },
	countAttackUPItem{AttackItem},
	m_player{player}
{
	menuSize_2 = 2;
	alphaTimer = 255;
	alphaCheck = false;

	GameDataManager::getInstance().SetItemBoXOpen(true);
}

void PlayerItemBox::initialize()
{
}

void PlayerItemBox::update(float deltaTime)
{
	PlayerInput();

	if (alphaCheck)
	{
		alphaTimer = min(alphaTimer + 5, 255);
		if (alphaTimer == 255) alphaCheck = false;
	}
	else
	{
		alphaTimer = max(alphaTimer - 5, 0);
		if (alphaTimer == 0) alphaCheck = true;
	}

	if(GetJoypadPOVState(DX_INPUT_PAD1, 0) == -1 && Keyboard::GetInstance().KeyStateUp(KEYCODE::F))
	{
		GameDataManager::getInstance().SetItemBoXOpen(false);
		die();
	}
}

void PlayerItemBox::draw() const
{
	Sprite::GetInstance().DrawSetCenter(SPRITE_ID::ITEMBOX, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::ITEMBOX).x/2, WINDOW_HEIGHT / 2));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaTimer);
	Sprite::GetInstance().Draw(SPRITE_ID::PAUSEITEM_TUKAUBACK, Vector2(1580.0f, static_cast<float>(420 + cursorPos_2 * 125)));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	const Vector2 NumSize = Sprite::GetInstance().GetSize(SPRITE_ID::NUMBER);

	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(1830.f ,445.f), static_cast<int>(NumSize.x / 10.0f) * countHPrecoverItem, 0, static_cast<int>(NumSize.x / 10.0f), static_cast<int>(NumSize.y));

	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(1830.f, 570.f), static_cast<int>(NumSize.x / 10.0f) * countAttackUPItem, 0, static_cast<int>(NumSize.x / 10.0f), static_cast<int>(NumSize.y));
}


void PlayerItemBox::receiveMessage(EventMessage message, void * param)
{
}

void PlayerItemBox::PlayerInput()	
{
	if (GamePad::GetInstance().RightStick().y < -0.5f || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN))
	{
		moveCursor2(1);
		alphaTimer = 255;
		alphaCheck = false;
	}

	if (GamePad::GetInstance().RightStick().y > 0.5f || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP))
	{
		moveCursor2(-1);
		alphaTimer = 255;
		alphaCheck = false;
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		int HPVal = 3;
		bool Attackup = true;
		switch (cursorPos_2)
		{
		case 0:
			if (countHPrecoverItem > 0)
			{
				m_player.lock()->receiveMessage(EventMessage::HP_RECOVER, reinterpret_cast<void*>(&HPVal));
				countHPrecoverItem = countHPrecoverItem - 1;
				Sound::GetInstance().PlaySE(SE_ID::ITEMUSE_SE);
			}
			break;
		case 1:
			if (countAttackUPItem > 0)
			{
				m_player.lock()->receiveMessage(EventMessage::ATTACK_UP, reinterpret_cast<void*>(&Attackup));
				countAttackUPItem = countAttackUPItem - 1;
				Sound::GetInstance().PlaySE(SE_ID::ITEMUSE_SE);
			}
			break;
		default:
			break;
		}
	}
}
