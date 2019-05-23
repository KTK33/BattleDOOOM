#pragma once

class ButtonR3
{
private:
	ButtonR3() {}
	~ButtonR3() = default;
public:
	static ButtonR3 &GetInstance() {
		static ButtonR3 g;
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
