#ifndef TEXTURE_ASSET_H_
#define TEXTURE_ASSET_H_

#include <string>
#include <unordered_map>

// テクスチャアセットクラス
class TextureAsset {
public:
    // コンストラクタ
    TextureAsset() = default;
    // デストラクタ
    ~TextureAsset();
    // 読み込み
    bool load(int id, const std::string& file_name);
    // 削除
    void erase(int id);
    // 消去
    void clear();
    // ハンドルの取得
    int operator [](int id) const;
    // コピー禁止
    TextureAsset(const TextureAsset&) = delete;
    TextureAsset& operator = (const TextureAsset&) = delete;
private:
    // テクスチャデータマップ
    std::unordered_map<int, int> asset_;
};

#endif
