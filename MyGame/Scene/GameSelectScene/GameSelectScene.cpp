#include "GameSelectScene.h"
#include "../Graphics/Graphics3D.h"
#include "../Texture/Sprite.h"
#include "../Input/InputInfoInc.h"
#include "../Game/Define.h"
#include "GameSelectSceneManager/GameSelectSceneManager.h"

GameSelectScene::GameSelectScene()
{}

void GameSelectScene::start()
{
	world_.initialize();
	menuSize_ = 2;
	cursorPos_ = 0;
	mCredit = false;
	mCreditPos = Vector2(0, -(float)WINDOW_HEIGHT);

	world_.add_actor(ActorGroup::System, new_actor<GameSelectSceneManager>(&world_));
}

void GameSelectScene::update(float deltaTime)
{
	world_.update(deltaTime);
	world_.send_message(EventMessage::SELECT_MODE_, reinterpret_cast<int*>(&cursorPos_));

	CreditSystem();

	if (mCreditPos.y != -(float)WINDOW_HEIGHT) return;

	if(ButtonUp::GetInstance().TriggerDown())
	{
		moveCursor(1);
	}
	if (ButtonDown::GetInstance().TriggerDown())
	{
		moveCursor(-1);
	}

	if (ButtonB::GetInstance().TriggerDown())
	{
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::PAUSEKETTEI_SE);

		switch (cursorPos_)
		{
		case 0:
			next_ = SceneType::SCENE_SHOOTING_LOAD;
			break;
		case 1:
			next_ = SceneType::SCENE_ACTION_LOAD;
			break;
		default:
			break;
		}
		isEnd_ = true;
	}
}

void GameSelectScene::draw() const
{
	Graphics3D::clear_color(255, 255, 255);

	Sprite::GetInstance().Draw(SPRITE_ID::SELECTBACK, Vector2(0, 0));
	Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SELECT_NAME, Vector2(WINDOW_WIDTH / 2, 150));

	switch (cursorPos_)
	{
	case 0:
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SELECT_SHOOTING_EX, Vector2(WINDOW_WIDTH / 2, 1080 - 76));
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SELECT_SHOOTING_DEC, Vector2(WINDOW_WIDTH / 2, 500));
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SELECT_ACTION, Vector2(WINDOW_WIDTH / 2, 700));
		Sprite::GetInstance().Draw(SPRITE_ID::SELECT_PUR_S, Vector2(WINDOW_WIDTH / 1.4f, 400));
		break;
	case 1:
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SELECT_ACTION_EX, Vector2(WINDOW_WIDTH / 2, 1080-76));
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SELECT_SHOOTING, Vector2(WINDOW_WIDTH / 2, 500));
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SELECT_ACTION_DEC, Vector2(WINDOW_WIDTH / 2, 700));
		Sprite::GetInstance().Draw(SPRITE_ID::SELECT_PUR_A, Vector2(WINDOW_WIDTH / 1.4f, 400));
		break;
	default:
		break;
	}

	world_.draw();

	Sprite::GetInstance().Draw(SPRITE_ID::CREDIT, mCreditPos);
	Sprite::GetInstance().Draw(SPRITE_ID::CREDIT_OPENBUTTON, Vector2(1600,1030));
}

void GameSelectScene::end()
{
}

void GameSelectScene::CreditSystem()
{
	if (ButtonStart::GetInstance().TriggerDown())
	{
		mCredit = !mCredit;
	}

	if (mCredit)
	{
		mCreditPos.y = MathHelper::Min(mCreditPos.y + 50.0f, 0.0f);
	}
	else
	{
		mCreditPos.y = MathHelper::Max(mCreditPos.y - 50.0f, -(float)WINDOW_HEIGHT);
	}
}
