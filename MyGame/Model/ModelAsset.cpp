#include "ModelAsset.h"
#include <DxLib.h>

// デストラクタ
ModelAsset::~ModelAsset() {
    clear();
}

// 読み込み
bool ModelAsset::load(int id, const std::string & file_name) {
    erase(id);
    asset_[id] = MV1LoadModel(file_name.c_str());
    return asset_[id] != -1;
}

// 削除
void ModelAsset::erase(int id) {
    if (asset_.count(id) > 0) {
        MV1DeleteModel(asset_[id]);
        asset_.erase(id);
    }
}

// 消去
void ModelAsset::clear() {
    for (const auto model : asset_) {
        MV1DeleteModel(model.first);
    }
    asset_.clear();
}

// ハンドルの取得
int ModelAsset::operator [](int id) const {
    return asset_.at(id);
}