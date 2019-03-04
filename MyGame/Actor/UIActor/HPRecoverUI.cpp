#include "HPRecoverUI.h"

HPRecoverUI::HPRecoverUI(int model, IWorld * world, const Vector3 & position):
	Actor(world,"HPUI",position),
	mesh_{model}
{
}

void HPRecoverUI::initialize()
{
}

void HPRecoverUI::update(float deltaTime)
{
	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
}

void HPRecoverUI::draw() const
{
	mesh_.draw();
}
