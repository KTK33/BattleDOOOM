#pragma once

class ButtonOption
{
private:
	ButtonOption() {}
	~ButtonOption() = default;
public:
	static ButtonOption &GetInstance() {
		static ButtonOption g;
		return g;
	}

	//�������u��
	bool TriggerDown();

	//���ꂽ�u��
	bool TriggerUp();

	//�����Ă��邩
	bool StateDown();

	//����Ă��邩
	bool StateUp();
};
