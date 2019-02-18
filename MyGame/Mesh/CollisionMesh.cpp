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

int CollisionMesh::ModelHandle()
{
	return model_;
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

bool CollisionMesh::collide_capsule(const Vector3 & start, const Vector3 & end, float radius, Vector3 * result)
{
	//当たったかどうか
	bool isHit = false;

	//始点、終点を取得
	VECTOR resultstart = start;
	VECTOR resultend = end;

	//足元を基準にした押し出し判定を行う
	if (collide_sphere(resultend, radius, &Vector3::VECTORToVector3(resultend))) {
		//足元からの押し出しベクトルを作成
		Vector3 moveVecbottom = VSub(resultend, end);
		//カプセルの始点に押し出しを適用
		resultstart = VAdd(resultstart, moveVecbottom);
		isHit = true;
	}
	//足元押し出し時点の始点、終点情報を保存
	VECTOR savestart = resultstart;
	VECTOR saveend = resultend;

	//頭を基準にした押し出し判定を行う
	if (collide_sphere(resultstart, radius, &Vector3::VECTORToVector3(resultstart))) {
		//頭からの押し出しベクトルを作成
		Vector3 moveVectop = VSub(resultstart, savestart);
		//カプセルの終点に押し出しを適用
		resultend = VAdd(resultend, moveVectop);
		isHit = true;
	}
	//ここまでで始点終点の押し出しが完了

	//中心を計算して返す
	//if(isHit)*result = (resultstart+ resultend)*0.5f;

	// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
	MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(model_, -1, resultstart, resultend, radius);

	for (int i = 0; i < HitDim.HitNum; i++) {
		VECTOR triangle[4]{
			HitDim.Dim[i].Position[0],
			HitDim.Dim[i].Position[1],
			HitDim.Dim[i].Position[2],
			HitDim.Dim[i].Position[0]
		};

		for (int loop = 0; loop < 3; loop++) {
			SEGMENT_SEGMENT_RESULT seg_seg_result;
			Segment_Segment_Analyse(&resultstart, &resultend, &triangle[i], &triangle[i + 1], &seg_seg_result);
			const auto distance = std::sqrt(seg_seg_result.SegA_SegB_MinDist_Square);
			if (distance <= radius) {
				isHit = true;
				VECTOR offset = VScale(VNorm(VSub(seg_seg_result.SegA_MinDist_Pos, seg_seg_result.SegB_MinDist_Pos)), radius - distance);
				resultstart = VAdd(resultstart, offset);
				resultend = VAdd(resultend, offset);
			}
		}
	}
	if (isHit)*result = (resultstart + resultend)*0.5f;

	//ポリゴンを開放する
	MV1CollResultPolyDimTerminate(HitDim);

	return isHit;

}

bool CollisionMesh::collide_capsule(const Vector3 & start1, const Vector3 & end1, float radius1, const Vector3 & start2, const Vector3 & end2, float radius2, Vector3 * result1, Vector3 * result2)
{
	//当たったかどうか
	bool isHit = false;

	//始点、終点を取得
	VECTOR resultstart1 = start1;
	VECTOR resultend1 = end1;
	VECTOR resultstart2 = start2;
	VECTOR resultend2 = end2;

	if (collide_sphere(resultend1, radius1, &Vector3::VECTORToVector3(resultend1))) {
		//足元からの押し出しベクトルを作成
		Vector3 moveVecbottom = VSub(resultend1, end1);
		//カプセルの始点に押し出しを適用
		resultend2 = VAdd(resultend2, moveVecbottom);
		isHit = true;
	}
	if (collide_sphere(resultend2, radius2, &Vector3::VECTORToVector3(resultend2))) {
		//足元からの押し出しベクトルを作成
		Vector3 moveVecbottom2 = VSub(resultend2, end2);
		//カプセルの始点に押し出しを適用
		resultend1 = VAdd(resultend1, moveVecbottom2);
		isHit = true;
	}

	//中心を計算して返す
	if (isHit) {
		*result1 = resultend1;
		*result2 = resultend2;
	}
	return isHit;

}
