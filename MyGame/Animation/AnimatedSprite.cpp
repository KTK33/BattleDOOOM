#include "AnimatedSprite.h"
#include "../Math/MathHelper.h"
#include <cmath>
#include <DxLib.h>

// デストラクタ
AnimatedSprite::~AnimatedSprite() {
    clear();
}

// 画像データを読み込む
void AnimatedSprite::load(const std::string& file_name, int row, int column) {
    // 画像データの読み込み
    load(file_name);
    // 画像サイズの取得
    int size_x = 0, size_y = 0;
    GetGraphSize(graph_, &size_x, &size_y);
    // 画像の分割
    int w = size_x / column;
    int h = size_y / row;
    for (int y = 0; y < size_y; y += h) {
        for (int x = 0; x < size_x; x += w) {
            div_graphs_.push_back(DerivationGraph(x, y, w, h, graph_));
        }
    }
}

// 画像データを読み込む
void AnimatedSprite::load(const std::string& file_name) {
    // 古いデータを削除
    clear();
    // 画像の読み込み
    graph_ = LoadGraph(file_name.c_str());
}

// 描画
void AnimatedSprite::draw(const Vector2& position) const {
    DrawGraphF(position.x, position.y, graph_, TRUE);
}

// 描画
void AnimatedSprite::draw(const Vector2& position, int x, int y, int w, int h) const {
    DrawRectGraphF(position.x, position.y, x, y, w, h, graph_, TRUE, FALSE);
}

// 描画
void AnimatedSprite::draw(int animation, float time, const Vector2& position, const Vector2& center, const Vector2& scale, float rotation) const {
    draw(find_key_frame(animation, time).second, position, center, scale, rotation);
}

// 描画
void AnimatedSprite::draw(int graph, const Vector2& position, const Vector2& center, const Vector2& scale, float rotation) const {
    DrawRotaGraph3F(position.x, position.y, center.x, center.y, scale.x, scale.y, MathHelper::ToRadians(rotation), div_graphs_[graph] , TRUE);
}

// アニメーションデータを追加
void AnimatedSprite::add_animation(int animation, int start_graph, int end_graph, float time) {
    animations_[animation].clear();
    for (int frame = 0; frame <= (end_graph - start_graph); ++frame) {
        add_key_frame(animation, (frame + 1) * time, start_graph + frame);
    }
}

// キーフレームを追加
void AnimatedSprite::add_key_frame(int animation, float time, int graph_no) {
    animations_[animation].emplace_back(time, graph_no);
}

// キーフレームを追加
void AnimatedSprite::add_key_frame(int animation, float time, int x, int y, int w, int h) {
    div_graphs_.push_back(DerivationGraph(x, y, w, h, graph_));
    add_key_frame(animation, time, int(div_graphs_.size()) - 1);
}

// アニメーション終了時間を取得
float AnimatedSprite::animation_end_time(int animation) const {
    return animations_.at(animation).back().first;
}

// 消去
void AnimatedSprite::clear() {
    if (graph_ != -1) {
        DeleteSharingGraph(graph_);
        graph_ = -1;
        div_graphs_.clear();
    }
    animations_.clear();
}

// アニメーションキーの検索
const AnimatedSprite::KeyFrame& AnimatedSprite::find_key_frame(int animation, float timer) const {
    const auto& key_frames = animations_.at(animation);
    timer = fmod(timer, animation_end_time(animation) + 1.0f);
    for (const auto& key_frame : key_frames) {
        if (timer <= key_frame.first) {
            return key_frame;
        }
    }
    return key_frames.back();
}

// end of file
