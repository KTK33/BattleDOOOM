#pragma once
#include "../Actor/Actor.h"

class AnyUI : public Actor {
public:
	AnyUI(IWorld* world, std::weak_ptr<Actor> p);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const;

private:
	std::weak_ptr<Actor> m_p{};
	int EnemyCount{ 3 };
};