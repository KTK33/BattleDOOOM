#include "GamePad.h"
#include <DxLib.h>

// ゲームパッドのボタン
const int GamePad::Left{ PAD_INPUT_LEFT };
const int GamePad::Right{ PAD_INPUT_RIGHT };
const int GamePad::Up{ PAD_INPUT_UP };
const int GamePad::Down{ PAD_INPUT_DOWN };
const int GamePad::A{ PAD_INPUT_1 };
const int GamePad::B{ PAD_INPUT_2 };
const int GamePad::X{ PAD_INPUT_3 };
const int GamePad::Y{ PAD_INPUT_4 };
const int GamePad::Back{ PAD_INPUT_7 };
const int GamePad::Start{ PAD_INPUT_8 };
const int GamePad::RightButton{ PAD_INPUT_6 };
const int GamePad::LeftButton{ PAD_INPUT_5 };
const int GamePad::RightTrigger{ PAD_INPUT_10 };

// 今回の入力状態
int GamePad::current_state_{ 0 };
// 前回の入力状態
int GamePad::previos_state_{ 0 };

// 初期化
void GamePad::initialize() {
    current_state_ = 0;
    previos_state_ = 0;
}

// 更新
void GamePad::update() {
    previos_state_ = current_state_;
    current_state_ = GetJoypadInputState(DX_INPUT_PAD1);
}

// ボタンが押されているか？
bool GamePad::state(int button) {
    return (current_state_ & button) != 0;
}

// ボタンが押されたか？
bool GamePad::trigger(int button) {
    return (current_state_ & ~previos_state_ & button) != 0;
}

// ボタンが離されたか？
bool GamePad::release(int button) {
    return (~current_state_ & previos_state_ & button) != 0;
}

// 終了処理
void GamePad::finalize() {
    initialize();
}

// end of file
