#include "EnemyDeadText.h"
#include "../ActorGroup.h"
#include "../../Game/Define.h"
#include "../Enemy/BossEnemy.h"
#include "../../Texture/Sprite.h"

EnemyDeadText::EnemyDeadText(IWorld * world):
	Actor(world, "EnemyDeadText",Vector3::Zero)
{
}

void EnemyDeadText::initialize()
{
	DeadEnemy = false;
	DummyDeadEnemy = false;
}

void EnemyDeadText::update(float deltaTime)
{
	if (DummyDeadEnemy){
		DummyDeadTextTime = max(DummyDeadTextTime - 1, 0);
		if (DummyDeadTextTime <= 0){
			DummyDeadTextTime = 90;
			DummyDeadEnemy = false;
		}
	}
}

void EnemyDeadText::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::BOSS_DEAD){
		DeadEnemy = true;
		world_->add_actor(ActorGroup::Enemy, new_actor<BossEnemy>(3, world_, Vector3{ 100.0f, 0.0f,0.0f }));
	}

	if (message == EventMessage::DUMMY_DEAD_ENEMY){
		DummyDeadEnemy = true;
		EnemyCount = EnemyCount - 1;
	}
}

void EnemyDeadText::draw() const
{
	if (DeadEnemy){
		Sprite::GetInstance().Draw(SPRITE_ID::TEXTBOSSAPPEAR, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::TEXTBOSSAPPEAR).x, WINDOW_HEIGHT));

		if (world_->find_actor(ActorGroup::Enemy, "DummyEnemy") != NULL){
			world_->send_message(EventMessage::DEAD_DUMMY_ENEMY, nullptr);
		}
	}

	if (DummyDeadEnemy) {
		Sprite::GetInstance().Draw(SPRITE_ID::TEXTDUMMYDEAD, Vector2(WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::TEXTDUMMYDEAD).x, WINDOW_HEIGHT));
	}

	SetFontSize(64);
	DrawFormatString(0, 600, GetColor(255, 255, 255), "%d", EnemyCount);
	SetFontSize(16);
}
