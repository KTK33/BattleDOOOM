#include "GameSelectScene.h"
#include "../Graphics/Graphics3D.h"
#include "../Texture/Sprite.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
#include "../Game/Define.h"

GameSelectScene::GameSelectScene()
{
}

void GameSelectScene::start()
{
	menuSize_ = 2;
	cursorPos_ = 0;
}

void GameSelectScene::update(float deltaTime)
{
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::UP) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP))
	{
		moveCursor(1);
	}
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::DOWN) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN))
	{
		moveCursor(-1);
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2) || Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
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
		break;
	case 1:
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SELECT_ACTION_EX, Vector2(WINDOW_WIDTH / 2, 1080-76));
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SELECT_SHOOTING, Vector2(WINDOW_WIDTH / 2, 500));
		Sprite::GetInstance().DrawSetCenter(SPRITE_ID::SELECT_ACTION_DEC, Vector2(WINDOW_WIDTH / 2, 700));
		break;
	default:
		break;
	}
}

void GameSelectScene::end()
{
}
