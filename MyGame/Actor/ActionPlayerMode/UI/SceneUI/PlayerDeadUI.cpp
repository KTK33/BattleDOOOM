#include "PlayerDeadUI.h"
#include "../Texture/Sprite.h"
#include "../Input/InputInfoInc.h"
#include "../Actor/CommonUIActor/FadeUI/FadeUI.h"
#include "../Scene/GameData/GameDataManager.h"

PlayerDeadUI::PlayerDeadUI(IWorld * world):
	Actor(world, "PlayerDeadUI", Vector3::Zero),
	mAlready{false}
{
	GameDataManager::getInstance().SetPlayerDead(true);
}

void PlayerDeadUI::update(float deltaTime)
{
	if (!mAlready)
	{
		if (ButtonB::GetInstance().TriggerDown())
		{
			world_->add_actor(ActorGroup::Fade, new_actor<FadeUI>(world_, 0, 2));
			mAlready = true;
		}
	}
}

void PlayerDeadUI::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::ACTIONPLAYERDEAD, 0, 0);
}
