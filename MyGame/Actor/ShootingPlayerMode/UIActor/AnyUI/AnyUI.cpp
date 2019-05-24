#include "AnyUI.h"
#include "../Texture/Sprite.h"

AnyUI::AnyUI(IWorld * world) :
	Actor(world, "AnyUI", Vector3::Zero),
	mEnemyCount{0}
{}

void AnyUI::update(float deltaTime)
{
	mEnemyCount = world_->count_actor(ActorGroup::Enemy);
}

void AnyUI::receiveMessage(EventMessage message, void * param)
{
}

void AnyUI::draw() const
{
	//MissonUI
	if (mEnemyCount > 0)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::MISSION_ENEMY_EXTERMINATION, Vector2(150, 75));

		const Vector2 Misson_NumSize = Sprite::GetInstance().GetSize(SPRITE_ID::MISSION_NUMBER);
		Sprite::GetInstance().DrawPart(SPRITE_ID::MISSION_NUMBER, Vector2(150 + Sprite::GetInstance().GetSize(SPRITE_ID::MISSION_ENEMY_EXTERMINATION).x, 90), static_cast<int>(Misson_NumSize.x / 10.0f) * mEnemyCount, 0, static_cast<int>(Misson_NumSize.x / 10.0f), static_cast<int>(Misson_NumSize.y));
	}
	else
	{
		Sprite::GetInstance().Draw(SPRITE_ID::MISSION_BOSS_DEFEAT, Vector2(150, 75));
	}

}
