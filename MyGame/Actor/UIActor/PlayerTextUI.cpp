#include "PlayerTextUI.h"
#include "../../Texture/Sprite.h"
#include "../../Scene/GameData/GameDataManager.h"
#include "../Player/PlayerItemBox.h"

PlayerTextUI::PlayerTextUI(IWorld * world):
	Actor(world,"PlayerText",Vector3::Zero)
{
	GetBulletCheck = false;
	BulletTextTimer = 0;
	GetRecoverCheck = false;
	RecoverTextTimer = 0;
	areladyItemBox = false;
	RecoverItemCount = 0;
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

	if (GameDataManager::getInstance().GetItemBoxOpen() == true){
		if (!areladyItemBox){
			world_->add_actor(ActorGroup::ItemBoxUI, new_actor<PlayerItemBox>(world_, RecoverItemCount));
			areladyItemBox = true;
		}
	}
	else
	{
		areladyItemBox = false;
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
		RecoverItemCount = *(int*)param;
	}

}

void PlayerTextUI::draw() const
{
	if (GetBulletCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::BULLETGETUI, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::BULLETGETUI).x, 0));
	}
	if (GetRecoverCheck)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::HPRECOVERTEXT, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::HPRECOVERTEXT).x, 0));
	}

}
