#include "AnyUI.h"
#include "../Texture/Sprite.h"

AnyUI::AnyUI(IWorld * world, std::weak_ptr<Actor> p) :
	Actor(world, "AnyUI", Vector3::Zero),
	m_p{ p }
{
	initialize();
}

void AnyUI::initialize()
{
}

void AnyUI::update(float deltaTime)
{
}

void AnyUI::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::DUMMY_DEAD_ENEMY) {
		EnemyCount = EnemyCount - 1;
	}
}

void AnyUI::draw() const
{
	//MissonUI
	if (EnemyCount > 0)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::MISSION_ENEMY_EXTERMINATION, Vector2(150, 75));

		const Vector2 Misson_NumSize = Sprite::GetInstance().GetSize(SPRITE_ID::MISSION_NUMBER);
		Sprite::GetInstance().DrawPart(SPRITE_ID::MISSION_NUMBER, Vector2(150 + Sprite::GetInstance().GetSize(SPRITE_ID::MISSION_ENEMY_EXTERMINATION).x, 90), static_cast<int>(Misson_NumSize.x / 10.0f) * EnemyCount, 0, static_cast<int>(Misson_NumSize.x / 10.0f), static_cast<int>(Misson_NumSize.y));
	}
	else
	{
		Sprite::GetInstance().Draw(SPRITE_ID::MISSION_BOSS_DEFEAT, Vector2(150, 75));
	}

}
