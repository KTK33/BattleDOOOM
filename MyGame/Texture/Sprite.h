#ifndef SPRITE_H_
#define SPRITE_H_

#include <vector>
#include <unordered_map>
#include "../Math/Vector2.h"
#include "../Animation/AnimatedSprite.h"

// スプライトクラス
class Sprite {
public:
    // 初期化
    static void initialize();
    // 画像ファイルの読み込み
    static void load(int id, const std::string& file_name);
    // 画像ファイルの読み込み (分割指定あり）
    static void load(int id, const std::string& file_name, int row, int column);
    // バインド
    static void bind(int id);
    // 描画（画像全体）
    static void draw(const Vector2& position);
    // 描画（画像の１部分を描画）
    static void draw(const Vector2& position, int x, int y, int w, int h);
    // 描画（分割番号指定）
    static void draw(int div_no, const Vector2& position, const Vector2& center = Vector2::Zero, const Vector2& scale = Vector2::One, float rotation = 0.0f);
    // 描画（アニメーション指定）
    static void draw(int animation, float time, const Vector2& position, const Vector2& center = Vector2::Zero, const Vector2& scale = Vector2::One, float rotation = 0.0f);
    // アニメーションの追加
    static void add_animation(int animation, int start, int end, float time);
    // キーフレームを追加
    static void add_key_frame(int animation, float time, int div_no);
    // キーフレームを追加
    static void add_key_frame(int animation, float time, int x, int y, int w, int h);
    // スプライトの削除
    static void erase(int id);
    // アニメーションの終了時間を取得
    static float get_animation_end_time(int animation);
    // 終了処理
    static void finalize();

private:
    // バインド中のＩＤ
    static int  id_;
    // スプライトデータ
    static std::unordered_map<int, AnimatedSprite> sprite_map_;
};

#endif

// end of file
