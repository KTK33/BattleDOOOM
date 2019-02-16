#include "AnyUI.h"
#include "../../Texture/Sprite.h"

AnyUI::AnyUI(IWorld * world, std::weak_ptr<Actor> p):
	Actor(world,"AnyUI",Vector3::Zero),
	m_p{p}
{
}

void AnyUI::initialize()
{
	m_playerHP = 0;
	m_playerHavegun = 0;
	m_playerGunRemain = 0;
}

void AnyUI::update(float deltaTime)
{
	if (world_->find_actor(ActorGroup::Player, "Player") != NULL){
		m_p.lock()->receiveMessage(EventMessage::PLAYER_HP, (void*)&m_playerHP);
		m_p.lock()->receiveMessage(EventMessage::PLAYER_REMAINGUN, (void*)&m_playerGunRemain);
		m_p.lock()->receiveMessage(EventMessage::PLAYER_HAVEGUN, (void*)&m_playerHavegun);
	}
}

void AnyUI::receiveMessage(EventMessage message, void * param)
{
	//if (message == EventMessage::PLAYER_HP)
	//{
	//	m_playerHP = *(int*)param;
	//}
	//if (message == EventMessage::PLAYER_REMAINGUN)
	//{
	//	m_playerGunRemain = *(int*)param;
	//}
	//if (message == EventMessage::PLAYER_HAVEGUN)
	//{
	//	m_playerHavegun = *(int*)param;
	//}

}

void AnyUI::draw() const
{
	//HP
	Sprite::GetInstance().Draw(SPRITE_ID::HP_UI, Vector2(0, WINDOW_HEIGHT));
	Sprite::GetInstance().DrawPart(SPRITE_ID::HP_GAUGE, Vector2(168, 22), 0, 0,
		Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).x / PlayerHP * m_playerHP, Sprite::GetInstance().GetSize(SPRITE_ID::HP_GAUGE).y);
	Sprite::GetInstance().Draw(SPRITE_ID::TEXTFRAME, Vector2((float)WINDOW_WIDTH - Sprite::GetInstance().GetSize(SPRITE_ID::TEXTFRAME).x, (float)WINDOW_HEIGHT));

	//弾数
	Vector2 GunFreamSize = Sprite::GetInstance().GetSize(SPRITE_ID::GUN_FREAM);
	Sprite::GetInstance().Draw(SPRITE_ID::GUN_FREAM, Vector2((float)WINDOW_WIDTH - GunFreamSize.x, GunFreamSize.y));
	Vector2 NumSize = Sprite::GetInstance().GetSize(SPRITE_ID::NUMBER);
	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER,Vector2((float)WINDOW_WIDTH - GunFreamSize.x*0.95f, (float)WINDOW_HEIGHT - GunFreamSize.y*0.8f),NumSize.x/10*m_playerGunRemain,0, NumSize.x / 10,NumSize.y); //セットされている弾数(１桁)
	Sprite::GetInstance().Draw(SPRITE_ID::THRASH,Vector2((float)WINDOW_WIDTH - GunFreamSize.x*0.7f, GunFreamSize.y*0.8f));//スラッシュ
	int m_P[2] = { m_playerHavegun / 10,m_playerHavegun % 10 };
	if (m_P[0] != 0) {
		Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2((float)WINDOW_WIDTH - GunFreamSize.x*0.5f, (float)WINDOW_HEIGHT - GunFreamSize.y*0.8f), NumSize.x / 10 * m_P[0], 0, NumSize.x / 10, NumSize.y); //セットされている弾数(１桁)
	}
	Sprite::GetInstance().DrawPart(SPRITE_ID::NUMBER, Vector2((float)WINDOW_WIDTH - GunFreamSize.x*0.3f, (float)WINDOW_HEIGHT - GunFreamSize.y*0.8f), NumSize.x / 10 * m_P[1], 0, NumSize.x / 10, NumSize.y); //セットされている弾数(１桁)
}
