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

	//�������u��
	bool TriggerDown();

	//���ꂽ�u��
	bool TriggerUp();

	//�����Ă��邩
	bool StateDown();

	//����Ă��邩
	bool StateUp();
};
