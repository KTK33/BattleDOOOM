#pragma once

class DPad
{
private:
	DPad() {}
	~DPad() = default;
public:
	static DPad &GetInstance() {
		static DPad g;
		return g;
	}

	//�\���L�[��
	bool GetUp();

	//�\���L�[�E
	bool GetRight();

	//�\���L�[��
	bool GetDown();

	//�\���L�[��
	bool GetLeft();
};
