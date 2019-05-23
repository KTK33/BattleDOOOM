#pragma once

class ButtonStart
{
private:
	ButtonStart() {}
	~ButtonStart() = default;
public:
	static ButtonStart &GetInstance() {
		static ButtonStart g;
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
