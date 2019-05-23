#pragma once

class ButtonX
{
private:
	ButtonX() {}
	~ButtonX() = default;
public:
	static ButtonX &GetInstance() {
		static ButtonX g;
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
