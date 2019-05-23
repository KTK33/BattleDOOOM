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

	//�������u��
	bool TriggerDown();

	//���ꂽ�u��
	bool TriggerUp();

	//�����Ă��邩
	bool StateDown();

	//����Ă��邩
	bool StateUp();
};
