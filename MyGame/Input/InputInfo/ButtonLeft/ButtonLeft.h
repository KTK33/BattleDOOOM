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

	//‰Ÿ‚µ‚½uŠÔ
	bool TriggerDown();

	//—£‚ê‚½uŠÔ
	bool TriggerUp();

	//‰Ÿ‚µ‚Ä‚¢‚é‚©
	bool StateDown();

	//—£‚ê‚Ä‚¢‚é‚©
	bool StateUp();
};
