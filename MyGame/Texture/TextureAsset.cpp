#include "TextureAsset.h"
#include <DxLib.h>

// �f�X�g���N�^
TextureAsset::~TextureAsset() {
    clear();
}

// �ǂݍ���
bool TextureAsset::load(int id, const std::string & file_name) {
    erase(id);
    asset_[id] = LoadGraph(file_name.c_str());
    return asset_[id] != -1;
}

// �폜
void TextureAsset::erase(int id) {
    if (asset_.count(id) > 0) {
        DeleteGraph(asset_[id]);
        asset_.erase(id);
    }
}

// ����
void TextureAsset::clear() {
    for (const auto image : asset_) {
        DeleteGraph(image.second);
    }
    asset_.clear();
}

// �n���h���̎擾
int TextureAsset::operator [](int id) const {
    return asset_.at(id);
}