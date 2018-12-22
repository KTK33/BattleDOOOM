#ifndef ANIMATED_SPRITE_H_
#define ANIMATED_SPRITE_H_

#include <unordered_map>
#include <vector>
#include "../Math/Vector2.h"

// アニメーション付きスプライトクラス
class AnimatedSprite {
public:
    // コンストラクタ
    AnimatedSprite() = default;
    // デストラクタ
    ~AnimatedSprite();
    // 画像ファイルの読み込み
    void load(const std::string& file_name);
    // 画像ファイルの読み込み
    void load(const std::string& file_name, int row, int column);
    // 描画（画像全体）
    void draw(const Vector2& position) const;
    // 描画（画像の一部分を描画）
    void draw(const Vector2& position, int x, int y, int w, int h) const;
    // 描画（分割番号指定）
    void draw(int no, const Vector2& position, const Vector2& center, const Vector2& scale, float rotation) const;
    // 描画（アニメーション指定）
    void draw(int animation, float time, const Vector2& position, const Vector2& center, const Vector2& scale, float rotation) const;
    // アニメーションの追加
    void add_animation(int animation, int start, int end, float time);
    // キーフレームを追加
    void add_key_frame(int animation, float time, int graph_no);
    // キーフレームを追加
    void add_key_frame(int animation, float time, int x, int y, int w, int h);
    // アニメーション終了時間を取得
    float animation_end_time(int animation) const;
    // 消去
    void clear();
    // コピー禁止
    AnimatedSprite(const AnimatedSprite& other) = delete;
    AnimatedSprite& operator = (const AnimatedSprite& other) = delete;

private:
    // 分割画像
    using DivGraphs = std::vector<int>;
    // キーフレーム
    using KeyFrame = std::pair<float, int>;
    // キーフレーム配列 
    using KeyFrames = std::vector<KeyFrame>;
    // アニメーション配列
    using Animations = std::unordered_map<int, KeyFrames>;

private:
    // キーフレームの検索
    const KeyFrame& find_key_frame(int animation, float time) const;

private:
    // 元画像
    int         graph_{ -1 };
    // 分割画像
    DivGraphs   div_graphs_;
    // アニメーションデータ
    Animations  animations_;
};

#endif

// end of file
