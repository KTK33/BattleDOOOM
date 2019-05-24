#pragma once

class ButtonDown
{
private:
	ButtonDown() {}
	~ButtonDown() = default;
public:
	static ButtonDown &GetInstance() {
		static ButtonDown g;
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
