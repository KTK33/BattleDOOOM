#pragma once

class ButtonStart
{
private:
	ButtonStart() {}
	~ButtonStart() = default;
public:
	static ButtonStart &GetInstance() {
		static ButtonStart g;
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
