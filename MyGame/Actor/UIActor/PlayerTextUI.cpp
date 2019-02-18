#include "PlayerTextUI.h"
#include "../../Texture/Sprite.h"

PlayerTextUI::PlayerTextUI(IWorld * world){
	GetBulletCheck = false;
	BulletTextTimer = 0;
	GetRecoverCheck = false;
	RecoverTextTimer = 0;
}

void PlayerTextUI::initialize()
{
}

void PlayerTextUI::update(float deltaTime)
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
}

void PlayerTextUI::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::GET_BULLET)
	{
		GetBulletCheck = true;
		BulletTextTimer = 0;
	}

	if (message == EventMessage::GET_HPRECOVER)
	{
		GetRecoverCheck = true;
		RecoverTextTimer = 0;
	}

}

void PlayerTextUI::draw() const
{
	if (GetBulletCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::BULLETGETUI, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::BULLETGETUI).x, WINDOW_HEIGHT));
	}
	if (GetRecoverCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::HPRECOVERTEXT, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::HPRECOVERTEXT).x, WINDOW_HEIGHT));
	}

}
