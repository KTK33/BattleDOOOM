#include "CollisionTriangle.h"
#include <cmath>

// コンストラクタ
CollisionTriangle::CollisionTriangle(const VECTOR& p1, const VECTOR& p2, const VECTOR& p3) :
    points_{ p1, p2, p3 } {
}

// 三角形の内側に座標があるか？
bool CollisionTriangle::is_inside(const VECTOR& point) const {
    // 三角形の重心座標を計算する
    float w1, w2, w3;
    TriangleBarycenter(points_[0], points_[1], points_[2], point, &w1, &w2, &w3);
    // 重心座標が三角形内にあるか？
    return (0.0f <= w1 && w1 <= 1.0f) && (0.0f <= w2 && w2 <= 1.0f) && (0.0f <= w3 && w3 <= 1.0f);
}

// 三角形の辺と球体の衝突判定
bool CollisionTriangle::collide_edge_and_sphere(const VECTOR& center, float radius, VECTOR* result) {
    bool is_collided = false;
    VECTOR result_center = center;
    const VECTOR edges[4]{ points_[0],  points_[1], points_[2], points_[0] };
    for (int i = 0; i < 3; ++i) {
        SEGMENT_POINT_RESULT segment_point_result;
        Segment_Point_Analyse(&edges[i], &edges[i + 1], &result_center, &segment_point_result);
        const auto distance = std::sqrt(segment_point_result.Seg_Point_MinDist_Square);
        if (distance <= radius) {
            VECTOR offset = VScale(VNorm(VSub(result_center, segment_point_result.Seg_MinDist_Pos)), radius - distance);
            result_center = VAdd(result_center, offset);
            is_collided = true;
        }
    }
    if (is_collided && (result != nullptr)) {
        *result = result_center;
    }
    return is_collided;
}

bool CollisionTriangle::collide_edge_and_capsule(const VECTOR & start, const VECTOR & end, float radius, VECTOR * result)
{
	bool is_collided = false;
	//if (collide_edge_and_sphere(start, radius, result))is_collided = true;
	Vector3 startResult;
	if (collide_edge_and_sphere(start, radius, (VECTOR*)&startResult))is_collided = true;
	if (collide_edge_and_sphere(end, radius, result))is_collided = true;



	auto result_start = start;
	auto result_end = end;
	//線分の始点、終点リスト
	const VECTOR edges[4]{ points_[0],points_[1],points_[2],points_[0] };
	for (int i = 0; i < 3; ++i) {
		SEGMENT_SEGMENT_RESULT segment_segment_result;//線分の衝突情報を入れる
													  //当たっているかを調べる(円からの距離を調べ、distanceを算出する事により判定している)
		Segment_Segment_Analyse(&edges[i], &edges[i + 1], &result_start, &result_end, &segment_segment_result);
		//Segment_Point_Analyse(&edges[i], &edges[i + 1], &result_center, &segment_point_result);
		const auto distance = std::sqrt(segment_segment_result.SegA_SegB_MinDist_Square);
		if (distance <= radius) {
			//VSub中心から最近Hit点を引いてる、VNormは正規化、VScaleはベクトルの大きさを拡大する、radius - distanceはめり込み量、offsetは押し出し量
			VECTOR offset = VScale(VNorm(VSub(segment_segment_result.SegB_MinDist_Pos, segment_segment_result.SegA_MinDist_Pos)), radius - distance);
			result_end = VAdd(result_end, offset);
			is_collided = true;
		}
	}


	return is_collided;
}
