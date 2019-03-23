#include "FadeUI.h"
#include "../../Texture/Sprite.h"
#include "../../Scene/GameData/GameDataManager.h"
#include "../Player/PlayerAdvent.h"

FadeUI::FadeUI(IWorld * world, int FadeCheck,int SceneNum):
	Actor(world,"FadeUI",Vector3::Zero),
	m_FadeCheck{FadeCheck},
	m_SceneNum{SceneNum}
{
	if (FadeCheck == 0)
	{
		FadeAlpha = 0;
	}
	else
	{
		FadeAlpha = 255;
	}
}

void FadeUI::initialize()
{
}

void FadeUI::update(float deltaTime)
{
	if (m_FadeCheck == 0)
	{
		FadeAlpha = min(FadeAlpha + 2.55f, 255);
		if (FadeAlpha == 255)
		{
			if (m_SceneNum == 1)
			{
				GameDataManager::getInstance().SetTitleCheck(true);
			}
		}
	}
	else
	{
		FadeAlpha = max(FadeAlpha - 2.55f, 0);
		if (FadeAlpha == 0)
		{
			if (m_SceneNum == 2)
			{
				world_->add_actor(ActorGroup::GameStartUI, new_actor<PlayerAdvent>(world_));
			}
		}
	}
}

void FadeUI::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, FadeAlpha);
	Sprite::GetInstance().Draw(SPRITE_ID::FADEBLACK, Vector2(0, 0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
