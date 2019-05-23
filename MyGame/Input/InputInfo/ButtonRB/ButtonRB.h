#pragma once

class ButtonRB
{
private:
	ButtonRB() {}
	~ButtonRB() = default;
public:
	static ButtonRB &GetInstance() {
		static ButtonRB g;
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
