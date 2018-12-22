#include "CollisionMesh.h"
#include "../Collision/CollisionTriangle.h"
#include <DxLib.h>

// バインド中のモデル
int CollisionMesh::model_{ -1 };
// モデルアセット
ModelAsset CollisionMesh::asset_;

// 初期化
void CollisionMesh::initialize() {
    finalize();
}

// 終了処理
void CollisionMesh::finalize() {
    asset_.clear();
    model_ = -1;
}

// 読み込み
bool CollisionMesh::load(int id, const std::string & file_name, int frame, int div_x, int div_y, int div_z) {
    auto result = asset_.load(id, file_name);
    if (result) {
        // 衝突判定情報を構築
        MV1SetupCollInfo(asset_[id], frame, div_x, div_y, div_z);
    }
    return result;
}

// 描画
void CollisionMesh::draw() {
    MV1DrawModel(model_);
}

// 削除
void CollisionMesh::erase(int id) {
    model_ = (model_ == asset_[id]) ? -1 : model_;
    asset_.erase(id);
}

// メッシュのバインド
void CollisionMesh::bind(int id) {
    model_ = asset_[id];
}

// 線分との衝突判定
bool CollisionMesh::collide_line(const Vector3 & start, const Vector3 & end, Vector3 * point, Vector3 * normal) {
    const auto coll_poly = MV1CollCheck_Line(model_, 0, start, end);
    if (coll_poly.HitFlag == TRUE) {
        if (point != nullptr) {
            *point = coll_poly.HitPosition;
        }
        if (normal != nullptr) {
            *normal = coll_poly.Normal;
        }
        return true;
    }
    return false;
}

// 球体との衝突判定
bool CollisionMesh::collide_sphere(const Vector3 & center, float radius, Vector3 * result) {
    // 球とメッシュの衝突判定
    const auto coll_poly = MV1CollCheck_Sphere(model_, 0, center, radius);
    // 衝突していなければ終了
    if (coll_poly.HitNum == 0) {
        // 衝突判定データの削除
        MV1CollResultPolyDimTerminate(coll_poly);
        return false;
    }
    VECTOR result_center = center;
    // ポリゴンの平面上に球体の位置を補正する
    for (int i = 0; i < coll_poly.HitNum; ++i) {
        // 平面上の座標の最近点座標を求める
        PLANE_POINT_RESULT plane_point_result;
        Plane_Point_Analyse(
            &coll_poly.Dim[i].Position[0],
            &coll_poly.Dim[i].Normal,
            &result_center,
            &plane_point_result);
        // 三角形の内部に平面上の座標の最近点座標があるか調べる
        if (CollisionTriangle(
            coll_poly.Dim[i].Position[0],
            coll_poly.Dim[i].Position[1],
            coll_poly.Dim[i].Position[2]).is_inside(plane_point_result.Plane_MinDist_Pos)) {
            // 法線ベクトルの方向へ球体を押し出す
            const auto distance = std::sqrt(plane_point_result.Plane_Pnt_MinDist_Square);
            const auto offset = VScale(coll_poly.Dim[i].Normal, radius - distance);
            result_center = VAdd(result_center, offset);
        }
    }
    // ポリゴンのエッジに重なっている場合に位置を補正する
    for (int i = 0; i < coll_poly.HitNum; ++i) {
        CollisionTriangle(
            coll_poly.Dim[i].Position[0],
            coll_poly.Dim[i].Position[1],
            coll_poly.Dim[i].Position[2]).collide_edge_and_sphere(result_center, radius, &result_center);
    }
    // 補正後の座標を設定
    if (result != nullptr) {
        *result = result_center;
    }
    // 衝突判定データの削除
    MV1CollResultPolyDimTerminate(coll_poly);
    return true;
}
