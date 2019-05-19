#include "ParamUI.h"
#include "../Texture/Sprite.h"
#include "../Game/Define.h"
#include "..\..\..\ActionPlayerMode\UI\HPUI\ActonPlayerHP.h"

void ParamUI::initialize()
{
	mHP = 0;
	mRemainGun = 0;
	mHaveGun = 0;
	mAimPos = Vector3::Zero;
	mAimCheck = false;
	mGunEmpty = false;
}

void ParamUI::SetHP(int hp)
{
	mHP = hp;
}

void ParamUI::SetRemainGun(int bullets)
{
	mRemainGun = bullets;
}

void ParamUI::SetHaveGun(int bullets)
{
	mHaveGun = bullets;
}

void ParamUI::SetAimPos(Vector3 pos,bool check)
{
	mAimPos = pos;
	mAimCheck = check;
}

void ParamUI::SetGunEmpty(bool check)
{
	mGunEmpty = check;
}

void ParamUI::draw() const
{
	//HP
	Sprite::GetInstance().Draw(SPRITE_ID::HP_UI, Vector2(0, 0));
	Sprite::GetInstance().DrawPart(SPRITE_ID::HP_GAUGE, Vector2(169, 22), 0, 0,
		static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).x / PlayerHP * mHP), static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).y));
	Sprite::GetInstance().Draw(SPRITE_ID::TEXTFRAME, Vector2(static_cast<float>(WINDOW_WIDTH) - Sprite::GetInstance().GetSize(SPRITE_ID::TEXTFRAME).x, 0));

	//íeêî
	Vector2 GunFreamSize = Sprite::GetInstance().GetSize(SPRITE_ID::GUN_FREAM);
	Sprite::GetInstance().Draw(SPRITE_ID::GUN_FREAM, Vector2(static_cast<float>(WINDOW_WIDTH) - GunFreamSize.x, (int)WINDOW_HEIGHT - GunFreamSize.y));
	Vector2 NumSize = Sprite::GetInstance().GetSize(SPRITE_ID::NUMBER);
	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(static_cast<float>(WINDOW_WIDTH) - GunFreamSize.x*0.95f, static_cast<float>(WINDOW_HEIGHT) - GunFreamSize.y*0.8f), static_cast<int>(NumSize.x / 10.0f) * mRemainGun, 0, static_cast<int>(NumSize.x / 10.0f), static_cast<int>(NumSize.y)); //ÉZÉbÉgÇ≥ÇÍÇƒÇ¢ÇÈíeêî(ÇPåÖ)
	Sprite::GetInstance().Draw(SPRITE_ID::THRASH, Vector2(static_cast<float>(WINDOW_WIDTH) - GunFreamSize.x*0.7f, static_cast<float>(WINDOW_HEIGHT) - GunFreamSize.y*0.8f));//ÉXÉâÉbÉVÉÖ
	int m_P[2] = { mHaveGun / 10,mHaveGun % 10 };
	if (m_P[0] != 0) {
		Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(static_cast<float>(WINDOW_WIDTH) - GunFreamSize.x*0.5f, static_cast<float>(WINDOW_HEIGHT) - GunFreamSize.y*0.8f), static_cast<int>(NumSize.x / 10.0f) * m_P[0], 0, static_cast<int>(NumSize.x / 10.0f), static_cast<int>(NumSize.y)); //ÉZÉbÉgÇ≥ÇÍÇƒÇ¢ÇÈíeêî(ÇPåÖ)
	}
	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(static_cast<float>(WINDOW_WIDTH) - GunFreamSize.x*0.3f, static_cast<float>(WINDOW_HEIGHT) - GunFreamSize.y*0.8f), static_cast<int>(NumSize.x / 10.0f) * m_P[1], 0, static_cast<int>(NumSize.x / 10.0f), static_cast<int>(NumSize.y)); //ÉZÉbÉgÇ≥ÇÍÇƒÇ¢ÇÈíeêî(ÇPåÖ)

	if (mAimCheck)
	{
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SIGHT, Vector2(ConvWorldPosToScreenPos(mAimPos).x, ConvWorldPosToScreenPos(mAimPos).y));
	}

	if (mGunEmpty)
	{
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::BULLET_EMPTY, Vector2(960, 800));
	}
}
