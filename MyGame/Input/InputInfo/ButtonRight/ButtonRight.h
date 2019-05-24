#pragma once

class ButtonRight
{
private:
	ButtonRight() {}
	~ButtonRight() = default;
public:
	static ButtonRight &GetInstance() {
		static ButtonRight g;
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
