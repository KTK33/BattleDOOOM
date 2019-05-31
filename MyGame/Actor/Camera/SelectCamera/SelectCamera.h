#pragma once

#include "../../Actor.h"

class SelectCamera : public Actor
{
public:
	SelectCamera(IWorld* world, std::weak_ptr<Actor> m_Player);
	virtual ~SelectCamera() override {}

private:
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	std::weak_ptr<Actor> m_player{};
};