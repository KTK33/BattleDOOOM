#include "GameOverUI.h"
#include "../Texture/Sprite.h"
#include "../Sound/Sound.h"
#include "../Input/InputInfoInc.h"
#include "../Actor/CommonUIActor/FadeUI/FadeUI.h"

GameOverUI::GameOverUI(IWorld * world):
	Actor(world,"GameOverBack",Vector3::Zero),
	GameOverBackAlpha{0},
	mAlready{false}
{
	initialize();
}

void GameOverUI::initialize()
{
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().PlayBGM(BGM_ID::LOSE_BGM, DX_PLAYTYPE_LOOP);
}

void GameOverUI::update(float deltaTime)
{
	GameOverBackAlpha = min(GameOverBackAlpha + 1, 225);

	if (!mAlready)
	{
		if (ButtonB::GetInstance().TriggerDown())
		{
			world_->add_actor(ActorGroup::Fade, new_actor<FadeUI>(world_, 0, 2));
			mAlready = true;
		}
	}
}

void GameOverUI::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, GameOverBackAlpha);
	Sprite::GetInstance().Draw(SPRITE_ID::GAMEOVERBACK, Vector2(0,0));

	Vector2 NameSize = Sprite::GetInstance().GetSize(SPRITE_ID::GAMEOVERNAME);
	Sprite::GetInstance().Draw(SPRITE_ID::GAMEOVERNAME, Vector2((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT - 900), NameSize/2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
