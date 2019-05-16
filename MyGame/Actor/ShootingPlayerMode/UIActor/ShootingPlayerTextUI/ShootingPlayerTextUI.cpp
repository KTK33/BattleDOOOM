#include "ShootingPlayerTextUI.h"
#include "../Texture/Sprite.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Sound/Sound.h"

ShootingPlayerTextUI::ShootingPlayerTextUI(IWorld * world):
	Actor(world,"PlayerText",Vector3::Zero)
{
	initialize();
}

void ShootingPlayerTextUI::initialize()
{
	GetBulletCheck = false;
	BulletTextTimer = 0;
	GetRecoverCheck = false;
	RecoverTextTimer = 0;
	AttackUpCheck = false;
	AttackUpTime = 600;
}

void ShootingPlayerTextUI::update(float deltaTime)
{
	if (GetBulletCheck)
	{
		GetRecoverCheck = false;
		BulletTextTimer = min(BulletTextTimer + 1, 60);
		if (BulletTextTimer == 60)
		{
			BulletTextTimer = 0;
			GetBulletCheck = false;
		}
	}
	if (GetRecoverCheck)
	{
		GetBulletCheck = false;
		RecoverTextTimer = min(RecoverTextTimer + 1, 60);
		if (RecoverTextTimer == 60)
		{
			RecoverTextTimer = 0;
			GetRecoverCheck = false;
		}
	}
	if (AttackUpCheck)
	{
		AttackUpTime = max(AttackUpTime - 1, 0);
		if (AttackUpTime == 0)
		{
			AttackUpTime = 600;
			AttackUpCheck = false;
		}
	}
}

void ShootingPlayerTextUI::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::GET_BULLET)
	{
		GetBulletCheck = true;
		BulletTextTimer = 0;
		Sound::GetInstance().PlaySE(SE_ID::ITEMGET_SE);
	}

	if (message == EventMessage::GET_HPRECOVER)
	{
		GetRecoverCheck = true;
		RecoverTextTimer = 0;
		Sound::GetInstance().PlaySE(SE_ID::ITEMGET_SE);
	}

	if (message == EventMessage::ATTACK_UP)
	{
		AttackUpCheck = *static_cast<bool*>(param);
	}

}

void ShootingPlayerTextUI::draw() const
{
	if (GetBulletCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::BULLETGETUI, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::BULLETGETUI).x, 0));
	}
	if (GetRecoverCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::HPRECOVERTEXT, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::HPRECOVERTEXT).x, 0));
	}
	if (AttackUpCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::ATTACK_UPNOW, Vector2(1300.0f, 150.0f));
	}
}
