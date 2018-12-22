#ifndef BACKGROUND_MUSIC_H_
#define BACKGROUND_MUSIC_H_

#include <string>
#include <unordered_map>

// BGMクラス
class BackgroundMusic {
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
    // BGMの再生
    static void play();
    // BGMの停止
    static void stop();
private:
    // バインド中のBGM
    static int bgm_;
    // BGMハンドル
    static std::unordered_map<int, int> bgm_map_;
};

#endif
