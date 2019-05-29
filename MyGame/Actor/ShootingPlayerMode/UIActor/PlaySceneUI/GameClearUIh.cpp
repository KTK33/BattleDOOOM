#include "GameClearUIh.h"
#include "../Texture/Sprite.h"
#include "../Sound/Sound.h"
#include "../Input/InputInfoInc.h"
#include "../Actor/CommonUIActor/FadeUI/FadeUI.h"

GameClearUI::GameClearUI(IWorld * world):
	Actor(world,"GameClearUI",Vector3::Zero),
	GameClearBackAlpha{0},
	mAlready{false}
{
	initialize();
}

void GameClearUI::initialize()
{
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().PlayBGM(BGM_ID::WIN_BGM);
}

void GameClearUI::update(float deltaTime)
{
	GameClearBackAlpha = min(GameClearBackAlpha + 1, 225);

	if (!mAlready)
	{
		if (ButtonB::GetInstance().TriggerDown())
		{
			world_->add_actor(ActorGroup::Fade, new_actor<FadeUI>(world_, 0, 2));
			mAlready = true;
		}
	}
}

void GameClearUI::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, GameClearBackAlpha);
	Sprite::GetInstance().Draw(SPRITE_ID::GAMECLEARBACK, Vector2(0, 0));

	const Vector2 NameSize = Sprite::GetInstance().GetSize(SPRITE_ID::GAMECLEARNAME);
	Sprite::GetInstance().Draw(SPRITE_ID::GAMECLEARNAME, Vector2(static_cast<float>(WINDOW_WIDTH) / 2, static_cast<float>(WINDOW_HEIGHT) - 900), NameSize / 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
