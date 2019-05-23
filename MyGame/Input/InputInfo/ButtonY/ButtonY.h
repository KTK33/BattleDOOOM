#pragma once

class ButtonY
{
private:
	ButtonY() {}
	~ButtonY() = default;
public:
	static ButtonY &GetInstance() {
		static ButtonY g;
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
