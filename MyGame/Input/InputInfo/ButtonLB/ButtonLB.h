#pragma once

class ButtonLB
{
private:
	ButtonLB() {}
	~ButtonLB() = default;
public:
	static ButtonLB &GetInstance() {
		static ButtonLB g;
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
