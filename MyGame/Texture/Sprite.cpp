#include "Sprite.h"
#include "../Math/MathHelper.h"
#include <cmath>
#include <DxLib.h>

// スプライトハンドル
int Sprite::id_{ -1 };
// スプライトデータ
std::unordered_map<int, AnimatedSprite> Sprite::sprite_map_;

// 初期化
void Sprite::initialize() {
    finalize();
}

// 画像ファイルの読み込み
void Sprite::load(int id, const std::string& file_name) {
    sprite_map_[id].load(file_name);
}

// 画像ファイルの読み込み (分割指定あり）
void Sprite::load(int id, const std::string& file_name, int row, int column) {
    sprite_map_[id].load(file_name, row, column);
}

// バインド
void Sprite::bind(int id) {
    id_ = id;
}

// 描画（画像全体）
void Sprite::draw(const Vector2& position) {
    sprite_map_[id_].draw(position);
}

// 描画（画像の１部分を描画）
void Sprite::draw(const Vector2& position, int x, int y, int w, int h) {
    sprite_map_[id_].draw(position, x, y, w, h);
}

// 描画（分割番号指定）
void Sprite::draw(int div_no, const Vector2& position, const Vector2& center, const Vector2& scale, float rotation) {
    sprite_map_[id_].draw(div_no, position, center, scale, rotation);
}

// 描画（アニメーション指定）
void Sprite::draw(int animation, float time, const Vector2& position, const Vector2& center, const Vector2& scale, float rotation) {
    sprite_map_[id_].draw(animation, time, position, center, scale, rotation);
}

// アニメーションの追加
void Sprite::add_animation(int animation, int start, int end, float time) {
    sprite_map_[id_].add_animation(animation, start, end, time);
}

// キーフレームを追加
void Sprite::add_key_frame(int animation, float time, int div_no) {
    sprite_map_[id_].add_key_frame(animation, time, div_no);
}

// キーフレームを追加
void Sprite::add_key_frame(int animation, float time, int x, int y, int w, int h) {
    sprite_map_[id_].add_key_frame(animation, time, x, y, w, h);
}

// スプライトの削除
void Sprite::erase(int id) {
    if (id == id_) {
        id_ = -1;
    }
    sprite_map_.erase(id);
}

// アニメーションの終了時間を取得
float Sprite::get_animation_end_time(int animation) {
    return sprite_map_[id_].animation_end_time(animation);
}

// グラフィックスの終了処理
void Sprite::finalize() {
    sprite_map_.clear();
    id_ = -1;
}

// end of file
