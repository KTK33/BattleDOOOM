#include "PlayerItemBox.h"
#include "../../Texture/Sprite.h"
#include "../../Input/GamePad.h"
#include "../../Scene/GameData/GameDataManager.h"

PlayerItemBox::PlayerItemBox(IWorld * world):
	Actor(world,"PlayerBox",Vector3::Zero),
	countHPrecoverItem{ 5 }
{
	menuSize_ = countHPrecoverItem;
}

void PlayerItemBox::initialize()
{
}

void PlayerItemBox::update(float deltaTime)
{
	PlayerInput();
}

void PlayerItemBox::draw() const
{
	//for (int u = 0; u < countHPrecoverItem; u++)
	//{
	//	Sprite::GetInstance().Draw(SPRITE_ID::HPRECOVERUI, Vector2(500 + 200 * u, 300));
	//}

	//DrawBox(500 + 200 * cursorPos_, 400, 700 + 200 * cursorPos_, 500, GetColor(255, 255, 255), TRUE);
}

void PlayerItemBox::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::GET_HPRECOVER)
	{
		countHPrecoverItem += 1;
	}
}

void PlayerItemBox::PlayerInput()	
{
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::RIGHT))
	{
		moveCursor(1);
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::LEFT))
	{
		moveCursor(-1);
	}

}
