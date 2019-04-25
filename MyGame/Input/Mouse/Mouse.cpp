#include "Mouse.h"
#include <DxLib.h>

// ゲームパッドのボタン
const int Mouse::Left{ PAD_INPUT_LEFT };
const int Mouse::Right{ PAD_INPUT_RIGHT };
const int Mouse::Middle{ PAD_INPUT_UP };

// 今回の入力状態
int Mouse::current_state_{ 0 };
// 前回の入力状態
int Mouse::previos_state_{ 0 };

// 初期化
void Mouse::initialize() {
    current_state_ = 0;
    previos_state_ = 0;
}

// 更新
void Mouse::update() {
    previos_state_ = current_state_;
    current_state_ = GetMouseInput();
}

// マウスカーソルの位置を取得
Vector2 Mouse::cursor_point() {
    int x = 0, y = 0;
    GetMousePoint(&x, &y);
    return Vector2(float(x), float(y));
}

// マウスカーソルの位置を設定
void Mouse::cursor_point(const Vector2& point) {
    SetMousePoint(int(point.x), int(point.y));
}

// マウスカーソルの表示
void Mouse::show_cursor() {
    SetMouseDispFlag(TRUE);
}

// マウスカーソルの非表示
void Mouse::hide_cursor() {
    SetMouseDispFlag(FALSE);
}

// ボタンが押されているか？
bool Mouse::state(int button) {
    return (current_state_ & button) != 0;
}

// ボタンが押されたか？
bool Mouse::trigger(int button) {
    return (current_state_ & ~previos_state_ & button) != 0;
}

// ボタンが離されたか？
bool Mouse::release(int button) {
    return (~current_state_ & previos_state_ & button) != 0;
}

// 終了処理
void Mouse::finalize() {
    current_state_ = 0;
    previos_state_ = 0;
}
