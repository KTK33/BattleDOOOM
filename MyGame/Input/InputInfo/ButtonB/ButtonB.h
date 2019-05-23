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

	//�������u��
	bool TriggerDown();

	//���ꂽ�u��
	bool TriggerUp();

	//�����Ă��邩
	bool StateDown();

	//����Ă��邩
	bool StateUp();
};
