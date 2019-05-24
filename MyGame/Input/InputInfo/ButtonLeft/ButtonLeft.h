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

	//�������u��
	bool TriggerDown();

	//���ꂽ�u��
	bool TriggerUp();

	//�����Ă��邩
	bool StateDown();

	//����Ă��邩
	bool StateUp();
};
