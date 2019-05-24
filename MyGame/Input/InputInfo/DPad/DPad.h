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

	//十字キー上
	bool GetUp();

	//十字キー右
	bool GetRight();

	//十字キー下
	bool GetDown();

	//十字キー左
	bool GetLeft();
};
