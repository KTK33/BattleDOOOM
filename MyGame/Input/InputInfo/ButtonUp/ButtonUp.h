#pragma once

class ButtonUp
{
private:
	ButtonUp() {}
	~ButtonUp() = default;
public:
	static ButtonUp &GetInstance() {
		static ButtonUp g;
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
