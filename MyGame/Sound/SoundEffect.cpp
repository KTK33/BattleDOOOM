#include "SoundEffect.h"
#include <DxLib.h>

// バインド中のSE
int SoundEffect::se_{ -1 };
// SEハンドル
std::unordered_map<int, int> SoundEffect::se_map_;

// 初期化
void SoundEffect::initialize() {
    finalize();
}

// 終了
void SoundEffect::finalize() {
    for (const auto& se : se_map_) {
        DeleteSoundMem(se.second);
    }
    se_map_.clear();
    se_ = -1;
}

// ファイルの読み込み
bool SoundEffect::load(int id, const std::string & file_name) {
    se_map_[id] = LoadSoundMem(file_name.c_str());
    return se_map_.at(id) != -1;
}

// 削除
void SoundEffect::erase(int id) {
    if (se_ == se_map_.at(id)) {
        se_ = -1;
    }
    DeleteSoundMem(se_map_.at(id));
    se_map_.erase(id);
}

// バインド
void SoundEffect::bind(int id) {
    se_ = se_map_.at(id);
}

// 再生
void SoundEffect::play() {
    // バックグラウンド再生
    PlaySoundMem(se_, DX_PLAYTYPE_BACK);
}
