#ifndef STATIC_MESH_H_
#define STATIC_MESH_H_

#include <string>
#include "../Math/MathH.h"
#include "../Model/ModelAsset.h"

// スタティックメッシュクラス
class StaticMesh {
public:
    // 初期化
    static void initialize();
    // 終了処理
    static void finalize();
    // 読み込み
    static bool load(int id, const std::string& file_name);
    // 削除
    static void erase(int id);
    // バインド
    static void bind(int id);
    // 描画
    static void draw();
    // ワールド変換行列を計算する
    static void transform(const Matrix& world);
private:
    // バインド中のモデル
    static int          model_;
    // ボーンのワールド変換行列
    static Matrix       world_matrix_;
    // モデルアセット
    static ModelAsset   asset_;
};


#endif
