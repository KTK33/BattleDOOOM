#pragma once

class ButtonA
{
private:
	ButtonA() {}
	~ButtonA() = default;
public:
	static ButtonA &GetInstance() {
		static ButtonA g;
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
