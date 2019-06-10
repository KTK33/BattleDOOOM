#include "RedSamuraiDeadUI.h"
#include "../Input/InputInfoInc.h"
#include "../Actor/CommonUIActor/FadeUI/FadeUI.h"
#include "../Texture/Sprite.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Sound/Sound.h"

RedSamuraiDeadUI::RedSamuraiDeadUI(IWorld * world):
	Actor(world, "RedSamuraiDeadUI", Vector3::Zero),
	mAlready{ false },
	meff{(int)EFFECT_ID::REDSAMURAI_DEAD},
	mTime{ 0 },
	mRedPos{ Vector3::Zero }
{
	menuSize_ = 2;
	cursorPos_ = 0;

	auto enemy = world_->find_actor(ActorGroup::Enemy, "RedSamurai").get();
	if (enemy == nullptr)return;
	mRedPos = enemy->Getposition();

	meff.stop();
	meff.set_endTime(120);
	meff.play();
}

void RedSamuraiDeadUI::update(float deltaTime)
{
	//エフェクトの設定
	meff.set_position(mRedPos);
	meff.set_scale(Vector3(5.0f, 5.0f, 5.0f));
	meff.set_rotation(Vector3::Zero);
	meff.update(deltaTime);
	
	mTime++;
	if (mTime == 120)
	{
		GameDataManager::getInstance().SetDeadBossEnemy(true);
		Sound::GetInstance().StopBGM();
		Sound::GetInstance().PlaySE(SE_ID::ACTION_WIN);
	}
	if (mTime < 121) return;

	if (Sound::GetInstance().IsPlaySE(SE_ID::ACTION_WIN)) return;

	//一度だけ実行
	if (!mAlready)
	{
		input();
		if (ButtonB::GetInstance().TriggerDown())
		{
			int type = 0;
			switch (cursorPos_) {
			case 0:
				type = 2;
				break;
			case 1:
				type = 3;
				break;
			default:
				break;
			}

			world_->add_actor(ActorGroup::Fade, new_actor<FadeUI>(world_, 0, type));
			mAlready = true;
		}
	}
}

void RedSamuraiDeadUI::draw() const
{
	meff.draw();
	if (mTime < 121) return;

	Sprite::GetInstance().Draw(SPRITE_ID::REDSAMURAIDEAD, 0, 0);

	if (!Sound::GetInstance().IsPlaySE(SE_ID::ACTION_WIN))
	{
		mSC.drawNext(cursorPos_);
	}
}

void RedSamuraiDeadUI::input()
{
	//カーソル上下
	if (ButtonUp::GetInstance().TriggerDown())
	{
		moveCursor(1);
	}
	if (ButtonDown::GetInstance().TriggerDown())
	{
		moveCursor(-1);
	}
}
