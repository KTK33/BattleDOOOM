#ifndef MODEL_ASSET_H_
#define MODEL_ASSET_H_

#include <unordered_map>
#include <string>

// モデルアセットクラス
class ModelAsset {
public:
    // コンストラクタ
    ModelAsset() = default;
    // デストラクタ
    ~ModelAsset();
    // 読み込み
    bool load(int id, const std::string& file_name);
    // 削除
    void erase(int id);
    // 消去
    void clear();
    // ハンドルの取得
    int operator [](int id) const;
    // コピー禁止
    ModelAsset(const ModelAsset&) = delete;
    ModelAsset& operator = (const ModelAsset&) = delete;
private:
    // モデルデータマップ
    std::unordered_map<int, int> asset_;
};

#endif
