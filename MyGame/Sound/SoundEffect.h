#ifndef SOUND_EFFECT_H_
#define SOUND_EFFECT_H_

#include <string>
#include <unordered_map>

// 効果音クラス
class SoundEffect {
public:
    // 初期化
    static void initialize();
    // 終了処理
    static void finalize();
    // 読み込み
    static bool load(int id, const std::string& file_name);
    // 削除
    static void erase(int id);
    // バインド
    static void bind(int id);
    // 効果音の再生
    static void play();
private:
    // バインド中のSE
    static int se_;
    // SEハンドル
    static std::unordered_map<int, int> se_map_;
};

#endif
