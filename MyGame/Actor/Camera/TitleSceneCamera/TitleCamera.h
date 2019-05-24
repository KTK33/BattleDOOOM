#pragma once

#include "../../Actor.h"

class TitleCamera : public Actor
{
public:
	TitleCamera(IWorld* world, std::weak_ptr<Actor> m_Player);
	virtual ~TitleCamera() override{}
		 
	virtual void update(float deltaTime) override;

private:
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	Vector2 m_FarPoint{ 0.f,0.f };

	float angle{ 0 };

	std::weak_ptr<Actor> m_player{};

	Actor* bullet;
};