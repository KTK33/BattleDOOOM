#ifndef SOUND_H_
#define SOUND_H_

#include <string>
#include <unordered_map>

// サウンドクラス
class Sound {
public:
    // 初期化
    static void initialize();
    // BGMファイルの読み込み
    static void load_bgm(int id, const std::string& file_name);
    // BGMの再生
    static void play_bgm(int id);
    // BGMの停止
    static void stop_bgm();
    // BGMの削除
    static void delete_bgm(int id);
    // SEファイルの読み込み
    static void load_se(int id, const std::string& file_name);
    // SEの再生
    static void play_se(int id);
    // SEの削除
    static void delete_se(int id);
    // 終了
    static void finalize();

private:
    // BGMハンドル
    static std::unordered_map<int, int> bgm_map_;
    // 再生中のBGM
    static int current_bgm_;
    // SEハンドル
    static std::unordered_map<int, int> se_map_;
};

#endif

// end of file
