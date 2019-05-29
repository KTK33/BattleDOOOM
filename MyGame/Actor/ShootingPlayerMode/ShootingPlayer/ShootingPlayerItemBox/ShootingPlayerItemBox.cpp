#include "ShootingPlayerItemBox.h"
#include "../Game/Define.h"
#include "../Texture/Sprite.h"
#include "../Input/InputInfoInc.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/ShootingPlayerParam/ShootingPlayerParam.h"

ShootingPlayerItemBox::ShootingPlayerItemBox(IWorld * world,int HPItem,int AttackItem, std::weak_ptr<Actor> player):
	Actor(world,"PlayerBox",Vector3::Zero),
	countHPrecoverItem{ HPItem },
	countAttackUPItem{AttackItem},
	m_player{player}
{
	initialize();
}

void ShootingPlayerItemBox::initialize()
{
	menuSize_2 = 2;
	alphaTimer = 255;
	alphaCheck = false;

	ShootingPlayerParam::getInstance().Set_ItemBoXOpen(true);
}

void ShootingPlayerItemBox::update(float deltaTime)
{
	PlayerInput();

	//選択カーソルの点滅
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

	//十字キー右を離したら閉じる
	if(!DPad::GetInstance().GetRight())
	{
		ShootingPlayerParam::getInstance().Set_ItemBoXOpen(false);
		die();
	}
}

void ShootingPlayerItemBox::draw() const
{
	Sprite::GetInstance().DrawSetCenter(SPRITE_ID::ITEMBOX, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::ITEMBOX).x/2, WINDOW_HEIGHT / 2));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaTimer);
	Sprite::GetInstance().Draw(SPRITE_ID::PAUSEITEM_TUKAUBACK, Vector2(1580.0f, static_cast<float>(420 + cursorPos_2 * 125)));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	const Vector2 NumSize = Sprite::GetInstance().GetSize(SPRITE_ID::NUMBER);

	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(1830.f ,445.f), static_cast<int>(NumSize.x / 10.0f) * countHPrecoverItem, 0, static_cast<int>(NumSize.x / 10.0f), static_cast<int>(NumSize.y));

	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(1830.f, 570.f), static_cast<int>(NumSize.x / 10.0f) * countAttackUPItem, 0, static_cast<int>(NumSize.x / 10.0f), static_cast<int>(NumSize.y));
}

void ShootingPlayerItemBox::PlayerInput()
{
	//右スティックで選択する
	if(RightStick::GetInstance().GetAngle().y < -0.5f)
	{
		moveCursor2(1);
		alphaTimer = 255;
		alphaCheck = false;
	}

	if (RightStick::GetInstance().GetAngle().y > 0.5f)
	{
		moveCursor2(-1);
		alphaTimer = 255;
		alphaCheck = false;
	}

	if(ButtonB::GetInstance().TriggerDown())
	{
		bool Attackup = true;
		switch (cursorPos_2)
		{
		case 0:
			if (countHPrecoverItem > 0)
			{
				m_player.lock()->receiveMessage(EventMessage::HP_RECOVER, (void*)&GetHpPoint);
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
