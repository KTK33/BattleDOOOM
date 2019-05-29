#include "RedSamuraiDeadUI.h"
#include "../Input/InputInfoInc.h"
#include "../Actor/CommonUIActor/FadeUI/FadeUI.h"
#include "../Texture/Sprite.h"
#include "../Scene/GameData/GameDataManager.h"

RedSamuraiDeadUI::RedSamuraiDeadUI(IWorld * world):
	Actor(world, "RedSamuraiDeadUI", Vector3::Zero),
	mAlready{ false }
{
	GameDataManager::getInstance().SetDeadBossEnemy(true);
}

void RedSamuraiDeadUI::update(float deltaTime)
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

void RedSamuraiDeadUI::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::REDSAMURAIDEAD, 0, 0);
}
