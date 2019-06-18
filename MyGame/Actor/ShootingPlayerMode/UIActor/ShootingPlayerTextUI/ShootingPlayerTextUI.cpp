#include "ShootingPlayerTextUI.h"
#include "../Texture/Sprite.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Sound/Sound.h"
#include "../Game/GameData/ShootingMode/ShootingPlayerData.h"

ShootingPlayerTextUI::ShootingPlayerTextUI(IWorld * world):
	Actor(world,"PlayerText",Vector3::Zero)
{
	initialize();
}

void ShootingPlayerTextUI::initialize()
{
	mGetBulletCheck = false;
	mBulletTextTimer = 0;
	mGetRecoverCheck = false;
	mRecoverTextTimer = 0;
	mAttackUpCheck = false;
	mAttackUpTime = AttackUpTime * 60;
}

void ShootingPlayerTextUI::update(float deltaTime)
{
	if (mGetBulletCheck)
	{
		mGetRecoverCheck = false;
		mBulletTextTimer = min(mBulletTextTimer + 1, TextTime*60);
		if (mBulletTextTimer == TextTime * 60)
		{
			mBulletTextTimer = 0;
			mGetBulletCheck = false;
		}
	}
	if (mGetRecoverCheck)
	{
		mGetBulletCheck = false;
		mRecoverTextTimer = min(mRecoverTextTimer + 1, TextTime * 60);
		if (mRecoverTextTimer == TextTime * 60)
		{
			mRecoverTextTimer = 0;
			mGetRecoverCheck = false;
		}
	}
	if (mAttackUpCheck)
	{
		mAttackUpTime = max(AttackUpTime - 1, 0);
		if (mAttackUpTime == 0)
		{
			mAttackUpTime = AttackUpTime * 60;
			mAttackUpCheck = false;
		}
	}
}

void ShootingPlayerTextUI::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::GET_BULLET)
	{
		mGetBulletCheck = true;
		mBulletTextTimer = 0;
		Sound::GetInstance().PlaySE(SE_ID::ITEMGET_SE);
	}

	if (message == EventMessage::GET_HPRECOVER)
	{
		mGetRecoverCheck = true;
		mRecoverTextTimer = 0;
		Sound::GetInstance().PlaySE(SE_ID::ITEMGET_SE);
	}

	if (message == EventMessage::ATTACK_UP)
	{
		mAttackUpCheck = *static_cast<bool*>(param);
	}
}

void ShootingPlayerTextUI::draw() const
{
	if (mGetBulletCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::BULLETGETUI, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::BULLETGETUI).x, 0));
	}
	if (mGetRecoverCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::HPRECOVERTEXT, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::HPRECOVERTEXT).x, 0));
	}
	if (mAttackUpCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::ATTACK_UPNOW, Vector2(1300.0f, 150.0f));
	}
}
