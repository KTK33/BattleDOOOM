#ifndef COLLISION_MESH_H_
#define COLLISION_MESH_H_

#include <string>
#include "../Math/Vector3.h"
#include "../Model/ModelAsset.h"
// 衝突判定用メッシュクラス
class CollisionMesh {
public:
    // 初期化
    static void initialize();
    // 終了処理
    static void finalize();
    // 読み込み
    static bool load(int id, const std::string& file_name, int frame = -1, int div_x = 32, int div_y = 8, int div_z = 32);
    // 削除
    static void erase(int id);
    // メッシュのバインド
    static void bind(int id);
    // 描画
    static void draw();
    // 線分との衝突判定
    static bool collide_line(const Vector3& start, const Vector3& end, Vector3* point = nullptr, Vector3* normal = nullptr);
    // 球体との衝突判定
    static bool collide_sphere(const Vector3& center, float radius, Vector3* result = nullptr);

private:
    // 衝突判定用モデルハンドラ
    static int  model_;
    // モデルアセット
    static ModelAsset asset_;
};

#endif