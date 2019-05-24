#pragma once

class ButtonUp
{
private:
	ButtonUp() {}
	~ButtonUp() = default;
public:
	static ButtonUp &GetInstance() {
		static ButtonUp g;
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
