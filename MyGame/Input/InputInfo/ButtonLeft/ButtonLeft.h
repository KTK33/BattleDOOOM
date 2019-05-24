#pragma once

class ButtonLeft
{
private:
	ButtonLeft() {}
	~ButtonLeft() = default;
public:
	static ButtonLeft &GetInstance() {
		static ButtonLeft g;
		return g;
	}

	//押した瞬間
	bool TriggerDown();

	//離れた瞬間
	bool TriggerUp();

	//押しているか
	bool StateDown();

	//離れているか
	bool StateUp();
};
