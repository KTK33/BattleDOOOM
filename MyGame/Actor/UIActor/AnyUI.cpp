#include "AnyUI.h"
#include "../../Texture/Sprite.h"

AnyUI::AnyUI(IWorld * world):
	Actor(world,"AnyUI",Vector3::Zero)
{
}

void AnyUI::initialize()
{
}

void AnyUI::update(float deltaTime)
{
}

void AnyUI::receiveMessage(EventMessage message, void * param)
{
}

void AnyUI::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::TEXTFRAME, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::TEXTFRAME).x, WINDOW_HEIGHT));
}
