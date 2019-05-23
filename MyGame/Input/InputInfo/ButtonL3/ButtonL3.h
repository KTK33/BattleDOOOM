#pragma once

class ButtonL3
{
private:
	ButtonL3() {}
	~ButtonL3() = default;
public:
	static ButtonL3 &GetInstance() {
		static ButtonL3 g;
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
