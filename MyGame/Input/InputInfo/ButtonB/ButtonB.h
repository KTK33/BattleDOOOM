#pragma once

class ButtonB
{
private:
	ButtonB() {}
	~ButtonB() = default;
public:
	static ButtonB &GetInstance() {
		static ButtonB g;
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
