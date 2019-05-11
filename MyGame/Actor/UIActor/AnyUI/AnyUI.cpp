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
	m_playerHP = 0;
	m_playerHavegun = 0;
	m_playerGunRemain = 0;
}

void AnyUI::update(float deltaTime)
{
	if (world_->find_actor(ActorGroup::Player, "Player") != NULL) {
		m_p.lock()->receiveMessage(EventMessage::PLAYER_HP, reinterpret_cast<void*>(&m_playerHP));
		m_p.lock()->receiveMessage(EventMessage::PLAYER_REMAINGUN, reinterpret_cast<void*>(&m_playerGunRemain));
		m_p.lock()->receiveMessage(EventMessage::PLAYER_HAVEGUN, reinterpret_cast<void*>(&m_playerHavegun));
	}
}

void AnyUI::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::DUMMY_DEAD_ENEMY) {
		EnemyCount = EnemyCount - 1;
	}
}

void AnyUI::draw() const
{
	//HP
	Sprite::GetInstance().Draw(SPRITE_ID::HP_UI, Vector2(0, 0));
	Sprite::GetInstance().DrawPart(SPRITE_ID::HP_GAUGE, Vector2(169, 22), 0, 0,
		static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).x / PlayerHP * m_playerHP), static_cast<int>(Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).y));
	Sprite::GetInstance().Draw(SPRITE_ID::TEXTFRAME, Vector2(static_cast<float>(WINDOW_WIDTH) - Sprite::GetInstance().GetSize(SPRITE_ID::TEXTFRAME).x, 0));

	//íeêî
	Vector2 GunFreamSize = Sprite::GetInstance().GetSize(SPRITE_ID::GUN_FREAM);
	Sprite::GetInstance().Draw(SPRITE_ID::GUN_FREAM, Vector2(static_cast<float>(WINDOW_WIDTH) - GunFreamSize.x, (int)WINDOW_HEIGHT- GunFreamSize.y));
	Vector2 NumSize = Sprite::GetInstance().GetSize(SPRITE_ID::NUMBER);
	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(static_cast<float>(WINDOW_WIDTH) - GunFreamSize.x*0.95f, static_cast<float>(WINDOW_HEIGHT) - GunFreamSize.y*0.8f), static_cast<int>(NumSize.x / 10.0f) * m_playerGunRemain, 0, static_cast<int>(NumSize.x / 10.0f), static_cast<int>(NumSize.y)); //ÉZÉbÉgÇ≥ÇÍÇƒÇ¢ÇÈíeêî(ÇPåÖ)
	Sprite::GetInstance().Draw(SPRITE_ID::THRASH, Vector2(static_cast<float>(WINDOW_WIDTH) - GunFreamSize.x*0.7f, static_cast<float>(WINDOW_HEIGHT)- GunFreamSize.y*0.8f));//ÉXÉâÉbÉVÉÖ
	int m_P[2] = { m_playerHavegun / 10,m_playerHavegun % 10 };
	if (m_P[0] != 0) {
		Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(static_cast<float>(WINDOW_WIDTH) - GunFreamSize.x*0.5f, static_cast<float>(WINDOW_HEIGHT) - GunFreamSize.y*0.8f), static_cast<int>(NumSize.x / 10.0f) * m_P[0], 0, static_cast<int>(NumSize.x / 10.0f), static_cast<int>(NumSize.y)); //ÉZÉbÉgÇ≥ÇÍÇƒÇ¢ÇÈíeêî(ÇPåÖ)
	}
	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2(static_cast<float>(WINDOW_WIDTH) - GunFreamSize.x*0.3f, static_cast<float>(WINDOW_HEIGHT) - GunFreamSize.y*0.8f), static_cast<int>(NumSize.x / 10.0f) * m_P[1], 0, static_cast<int>(NumSize.x / 10.0f), static_cast<int>(NumSize.y)); //ÉZÉbÉgÇ≥ÇÍÇƒÇ¢ÇÈíeêî(ÇPåÖ)

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
