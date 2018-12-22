#include "SoundEffect.h"
#include <DxLib.h>

// �o�C���h����SE
int SoundEffect::se_{ -1 };
// SE�n���h��
std::unordered_map<int, int> SoundEffect::se_map_;

// ������
void SoundEffect::initialize() {
    finalize();
}

// �I��
void SoundEffect::finalize() {
    for (const auto& se : se_map_) {
        DeleteSoundMem(se.second);
    }
    se_map_.clear();
    se_ = -1;
}

// �t�@�C���̓ǂݍ���
bool SoundEffect::load(int id, const std::string & file_name) {
    se_map_[id] = LoadSoundMem(file_name.c_str());
    return se_map_.at(id) != -1;
}

// �폜
void SoundEffect::erase(int id) {
    if (se_ == se_map_.at(id)) {
        se_ = -1;
    }
    DeleteSoundMem(se_map_.at(id));
    se_map_.erase(id);
}

// �o�C���h
void SoundEffect::bind(int id) {
    se_ = se_map_.at(id);
}

// �Đ�
void SoundEffect::play() {
    // �o�b�N�O���E���h�Đ�
    PlaySoundMem(se_, DX_PLAYTYPE_BACK);
}
