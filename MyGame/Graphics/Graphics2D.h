#ifndef GRAPHICS_2D_H_
#define GRAPHICS_2D_H_

#include "../Math/Vector2.h"
#include "../Animation/AnimatedSprite.h"
#include <string>
#include <unordered_map>

// グラフィックスクラス
class Graphics2D {
public:
    // 初期化
    static void initialize();
    // 画像ファイルの読み込み
    static void load_sprite(int id, const std::string& file_name);
    // 画像ファイルの読み込み (分割指定あり）
    static void load_sprite(int id, const std::string& file_name, int row, int column);
    // 描画（画像全体）
    static void draw_sprite(int id, const Vector2& position);
    // 描画（画像の１部分を描画）
    static void draw_sprite(int id, const Vector2& position, int x, int y, int w, int h);
    // 描画（分割番号指定）
    static void draw_sprite(int id, int div_no, const Vector2& position, const Vector2& center = Vector2::Zero, const Vector2& scale = Vector2::One, float rotation = 0.0f);
    // 描画（アニメーション指定）
    static void draw_sprite(int id, int animation, float time, const Vector2& position, const Vector2& center = Vector2::Zero, const Vector2& scale = Vector2::One, float rotation = 0.0f);
    // アニメーションの追加
    static void add_sprite_animation(int id, int animation, int start, int end, float time);
    // キーフレームを追加
    static void add_sprite_key_frame(int id, int animation, float time, int div_no);
    // キーフレームを追加
    static void add_sprite_key_frame(int id, int animation, float time, int x, int y, int w, int h);
    // スプライトの削除
    static void delete_sprite(int id);
    // アニメーションの終了時間を取得
    static float get_sprite_animation_end_time(int id, int animation);
    // 消去カラーの設定
    static void clear_color(float r, float g, float b);
    // グラフィックスの終了処理
    static void finalize();

private:
    // スプライトデータ
    static std::unordered_map<int, AnimatedSprite> sprite_map_;
};

#endif

// end of file
