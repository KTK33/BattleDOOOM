#include "BackgroundMusic.h"
#include <DxLib.h>

// バインド中のBGM
int BackgroundMusic::bgm_{ -1 };
// BGMハンドル
std::unordered_map<int, int> BackgroundMusic::bgm_map_;

// 初期化
void BackgroundMusic::initialize() {
    finalize();
}

// 終了処理
void BackgroundMusic::finalize() {
    for (const auto& bgm : bgm_map_) {
        DeleteSoundMem(bgm.second);
    }
    bgm_map_.clear();
    bgm_ = -1;
}

// 読み込み
bool BackgroundMusic::load(int id, const std::string & file_name) {
    bgm_map_[id] = LoadSoundMem(file_name.c_str(), 1);
    return bgm_map_.at(id) != -1;
}

// 削除
void BackgroundMusic::erase(int id) {
    if (bgm_ == bgm_map_.at(id)) {
        bgm_ = -1;
    }
    DeleteSoundMem(bgm_map_.at(id));
    bgm_map_.erase(id);
}

// バインド
void BackgroundMusic::bind(int id) {
    if (bgm_map_.at(id) != bgm_) {
        stop();
    }
    bgm_ = bgm_map_.at(id);
}

// 再生
void BackgroundMusic::play() {
    // バックグラウンド再生、ループ再生
    PlaySoundMem(bgm_, DX_PLAYTYPE_BACK | DX_PLAYTYPE_LOOP);
}

// 停止
void BackgroundMusic::stop() {
    StopSoundMem(bgm_);
}

