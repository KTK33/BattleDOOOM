#pragma once

class ButtonL3
{
private:
	ButtonL3() {}
	~ButtonL3() = default;
public:
	static ButtonL3 &GetInstance() {
		static ButtonL3 g;
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
