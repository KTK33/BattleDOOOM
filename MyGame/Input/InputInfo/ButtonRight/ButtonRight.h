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

	//�������u��
	bool TriggerDown();

	//���ꂽ�u��
	bool TriggerUp();

	//�����Ă��邩
	bool StateDown();

	//����Ă��邩
	bool StateUp();
};
