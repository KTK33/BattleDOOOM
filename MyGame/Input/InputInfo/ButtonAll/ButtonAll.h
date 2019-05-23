#pragma once

class ButtonAll
{
private:
	ButtonAll() {}
	~ButtonAll() = default;
public:
	static ButtonAll &GetInstance() {
		static ButtonAll g;
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
