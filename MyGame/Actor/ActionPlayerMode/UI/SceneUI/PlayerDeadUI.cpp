#include "PlayerDeadUI.h"
#include "../Texture/Sprite.h"
#include "../Input/InputInfoInc.h"
#include "../Actor/CommonUIActor/FadeUI/FadeUI.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Sound/Sound.h"

PlayerDeadUI::PlayerDeadUI(IWorld * world) :
	Actor(world, "PlayerDeadUI", Vector3::Zero),
	mAlready{ false },
	meff{ (int)EFFECT_ID::ACTION_PLAYER_DEAD },
	mTime{ 0 },
	mPlayerPos{Vector3::Zero}
{
	menuSize_ = 2;
	cursorPos_ = 1;

	auto player = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player == nullptr)return;
	mPlayerPos = player->Getposition();

	meff.stop();
	meff.set_endTime(150);
	meff.play();
}

void PlayerDeadUI::update(float deltaTime)
{
	//エフェクトの設定
	meff.set_position(mPlayerPos);
	meff.set_scale(Vector3(7.0f,7.0f, 7.0f));
	meff.set_rotation(Vector3::Zero);
	meff.update(deltaTime);

	mTime++;
	if (mTime == 150)
	{
		GameDataManager::getInstance().SetPlayerDead(true);
		Sound::GetInstance().StopBGM();
		Sound::GetInstance().PlaySE(SE_ID::ACTION_LOSE);
	}

	if (mTime < 151) return;

	if (Sound::GetInstance().IsPlaySE(SE_ID::ACTION_LOSE)) return;

	//一度だけ実行
	if (!mAlready)
	{
		input();
		if (ButtonB::GetInstance().TriggerDown())
		{
			int type = 0;
			switch (cursorPos_){
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

void PlayerDeadUI::draw() const
{
	meff.draw();
	if (mTime < 151) return;

	Sprite::GetInstance().Draw(SPRITE_ID::ACTIONPLAYERDEAD, 0, 0);

	if (!Sound::GetInstance().IsPlaySE(SE_ID::ACTION_LOSE))
	{
		mSC.drawNext(cursorPos_);
	}
}

void PlayerDeadUI::input()
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
