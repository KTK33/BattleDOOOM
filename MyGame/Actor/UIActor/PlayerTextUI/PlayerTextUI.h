#pragma once
#include "../Actor/Actor.h"

class PlayerTextUI : public Actor
{
public:
	PlayerTextUI(IWorld* world);
	virtual ~PlayerTextUI()override {}

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const override;

private:

	bool GetBulletCheck;
	int BulletTextTimer;
	bool GetRecoverCheck;
	int RecoverTextTimer;
	bool AttackUpCheck;
	int AttackUpTime;
};