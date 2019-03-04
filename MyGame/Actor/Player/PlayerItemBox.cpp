#include "PlayerItemBox.h"
#include "../../Texture/Sprite.h"
#include "../../Input/GamePad.h"
#include "../../Scene/GameData/GameDataManager.h"
#include "../UIActor/HPRecoverUI.h"

PlayerItemBox::PlayerItemBox(IWorld * world,int HPItem):
	Actor(world,"PlayerBox",Vector3::Zero),
	countHPrecoverItem{ HPItem }
{
	menuSize_ = 3;

	world_->add_actor(ActorGroup::ItemBoxUIUI, new_actor<HPRecoverUI>(6,world_, Vector3(0,-30,0)));
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
	Sprite::GetInstance().Draw(SPRITE_ID::HPRECOVERUI, Vector2(700 , 300));

	DrawBox(500 + 200 * cursorPos_, 400, 700 + 200 * cursorPos_, 500, GetColor(255, 255, 255), TRUE);

	Vector2 NumSize = Sprite::GetInstance().GetSize(SPRITE_ID::NUMBER);
	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(150 ,90), NumSize.x / 10 * countHPrecoverItem, 0, NumSize.x / 10, NumSize.y);}

void PlayerItemBox::receiveMessage(EventMessage message, void * param)
{
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

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
	{
		die();
	}
}
