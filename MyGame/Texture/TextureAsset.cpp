#include "TextureAsset.h"
#include <DxLib.h>

// デストラクタ
TextureAsset::~TextureAsset() {
    clear();
}

// 読み込み
bool TextureAsset::load(int id, const std::string & file_name) {
    erase(id);
    asset_[id] = LoadGraph(file_name.c_str());
    return asset_[id] != -1;
}

// 削除
void TextureAsset::erase(int id) {
    if (asset_.count(id) > 0) {
        DeleteGraph(asset_[id]);
        asset_.erase(id);
    }
}

// 消去
void TextureAsset::clear() {
    for (const auto image : asset_) {
        DeleteGraph(image.second);
    }
    asset_.clear();
}

// ハンドルの取得
int TextureAsset::operator [](int id) const {
    return asset_.at(id);
}