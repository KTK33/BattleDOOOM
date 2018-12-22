#include "BackgroundMusic.h"
#include <DxLib.h>

// �o�C���h����BGM
int BackgroundMusic::bgm_{ -1 };
// BGM�n���h��
std::unordered_map<int, int> BackgroundMusic::bgm_map_;

// ������
void BackgroundMusic::initialize() {
    finalize();
}

// �I������
void BackgroundMusic::finalize() {
    for (const auto& bgm : bgm_map_) {
        DeleteSoundMem(bgm.second);
    }
    bgm_map_.clear();
    bgm_ = -1;
}

// �ǂݍ���
bool BackgroundMusic::load(int id, const std::string & file_name) {
    bgm_map_[id] = LoadSoundMem(file_name.c_str(), 1);
    return bgm_map_.at(id) != -1;
}

// �폜
void BackgroundMusic::erase(int id) {
    if (bgm_ == bgm_map_.at(id)) {
        bgm_ = -1;
    }
    DeleteSoundMem(bgm_map_.at(id));
    bgm_map_.erase(id);
}

// �o�C���h
void BackgroundMusic::bind(int id) {
    if (bgm_map_.at(id) != bgm_) {
        stop();
    }
    bgm_ = bgm_map_.at(id);
}

// �Đ�
void BackgroundMusic::play() {
    // �o�b�N�O���E���h�Đ��A���[�v�Đ�
    PlaySoundMem(bgm_, DX_PLAYTYPE_BACK | DX_PLAYTYPE_LOOP);
}

// ��~
void BackgroundMusic::stop() {
    StopSoundMem(bgm_);
}

