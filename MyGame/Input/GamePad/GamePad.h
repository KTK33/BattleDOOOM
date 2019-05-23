#pragma once

#include <Dxlib.h>
#include "../Math/Vector2.h"
#include <unordered_map>
#include <VECTOR>
#include <array>

#include "../InputType.h"

class GamePad
{
private:
	GamePad();
	~GamePad() = default;
public:
	static GamePad &GetInstance() {
		static GamePad g;
		return g;
	}

	///<summary>
	/// 指定のパッドの指定のボタンが入力された瞬間か調べる
	///</summary>
	bool ButtonTriggerDown(int button, int pad = PADNUM::PAD1);
	///<summary>
	/// 指定のパッドの指定のボタンが入力されているか調べる
	///</summary>
	bool ButtonStateDown(int button, int pad = PADNUM::PAD1);
	///<summary>
	/// 指定のパッドの指定のボタンが離れた瞬間か調べる
	///</summary>
	bool ButtonTriggerUp(int button, int pad = PADNUM::PAD1);
	///<summary>
	/// 指定のパッドの指定のボタンが離れているか調べる
	///</summary>
	bool ButtonStateUp(int button, int pad = PADNUM::PAD1);
	/// <summary>
	/// いずれかのボタンが入力された瞬間か調べる
	/// </summary>
	bool AnyTriggerDown(int pad = PADNUM::PAD1);
	/// <summary>
	/// いずれかのボタンが入力されているか調べる
	/// </summary>
	bool AnyStateDown(int pad = PADNUM::PAD1);
	/// <summary>
	/// いずれかのボタンが離れた瞬間か調べる
	/// </summary>
	bool AnyTriggerUp(int pad = PADNUM::PAD1);
	/// <summary>
	/// いずれかのボタンが離れているか調べる
	/// </summary>
	bool AnyStateUp(int pad = PADNUM::PAD1);
	///<summary>
	/// 指定のパッドのPOVが入力された瞬間の方向を受け取る
	///</summary>
	int POVTriggerDown(int pad = PADNUM::PAD1);
	///<summary>
	/// 指定のパッドのPOVが入力された方向を受け取る
	///</summary>
	int POVStateDown(int pad = PADNUM::PAD1);
	///<summary>
	/// 指定のパッドのアナログスティックの入力具合を調べる
	/// (X = -1.0～1.0, Y = -1.0～1.0)
	///</summary>
	Vector2 Stick(int pad = PADNUM::PAD1);
	///<summary>
	/// 現フレームの1番目コントローラのスティック入力を受け取る
	///</summary>
	Vector2 GetCurrentStick();
	///<summary>
	/// 前フレームの1番目コントローラのスティック入力を受け取る
	///</summary>
	Vector2 GetPreviousStick();
	///<summary>
	/// 現フレームの1番目コントローラの右スティック入力を受け取る
	///</summary>
	Vector2 GetCurrentRightStick();
	///<summary>
	/// 前フレームの1番目コントローラの右スティック入力を受け取る
	///</summary>
	Vector2 GetPreviousRightStick();
	///<summary>
	/// 指定のパッドの右アナログスティックの入力具合を調べる
	/// (X = -1.0～1.0, Y = -1.0～1.0)
	///</summary>
	Vector2 RightStick(int pad = PADNUM::PAD1);
	///<summary>
	/// 指定のパッドの振動を開始する
	///</summary>
	void VibrationStart(int power, int time, int pad = PADNUM::PAD1);
	///<summary>
	/// 指定のパッドの振動を終了する
	///</summary>
	void VibrationEnd(int pad = PADNUM::PAD1);
	void Update();
private:
	void Exception(int pad, int button);

	//std::unordered_map<int, std::array<int, 50000>> m_currentbutton;// 現在のボタン状態
	//std::unordered_map<int, std::array<int, 50000>> m_previosbutton;// 1フレーム前のボタン状態

	//<パッド番号, <PAD_INPUT_1など, カウンター>
	std::unordered_map<int, std::unordered_map<int, int>> m_onbuttons;
	std::unordered_map<int, std::unordered_map<int, int>> m_offbuttons;

	std::unordered_map<int, int> m_onpovbuttons;

	std::vector<int> m_inputbuttons;// ボタン入力判定達
	std::vector<int> m_pads;// パッド番号達

	Vector2 curStick_;//現フレームのスティック入力
	Vector2 prevStick_;//前フレームのスティック入力

	Vector2 curRightStick_;//現フレームの右スティック入力
	Vector2 prevRightStick_;//前フレームの右スティック入力
};