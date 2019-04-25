#ifndef MOUSE_H_
#define MOUSE_H_

#include "../Math/Vector2.h"

// マウスクラス
class Mouse {
public:
    // マウスのボタン
    static const int Left;
    static const int Right;
    static const int Middle;

    // 初期化
    static void initialize();
    // 更新
    static void update();
    // マウスカーソルの位置を取得
    static Vector2 cursor_point();
    // マウスカーソルの位置を設定
    static void cursor_point(const Vector2& point);
    // マウスカーソルの表示
    static void show_cursor();
    // マウスカーソルの非表示
    static void hide_cursor();
    // ボタンが押されているか？
    static bool state(int button);
    // ボタンが押されたか？
    static bool trigger(int button);
    // ボタンが離されたか？
    static bool release(int button);
    // 終了処理
    static void finalize();

private:
    // 今回の入力状態
    static int current_state_;
    // 前回の入力状態
    static int previos_state_;
};

#endif

// end of file
