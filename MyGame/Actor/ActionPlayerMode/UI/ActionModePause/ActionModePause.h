#pragma once
#include "../Actor/Actor.h"
#include "../Scene/Menu.h"

//アクションモードのポーズクラス
class ActionModePause : public Actor, public Menu {
public:
	ActionModePause(IWorld* world);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void receiveMessage(EventMessage message, void * param) override;

	virtual void draw() const override;

	//入力
	void PlayerInput();

private:
	bool PauseDecision; //ポーズの決定状態

	bool areladySystemOpen;
};