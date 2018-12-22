//#include "Collision.h"
//#include "../../Conv/DXConverter.h"
//
//// 球とOBBの衝突判定
//CollisionParameter Collision::Sphere_vs_OBB(CollisionParameter & colpara, Sphere & sphere, Box & box)
//{
//	ClosestPtPointOBB(colpara, sphere.centerPos, box);
//	Vector3 v = colpara.colPos - sphere.centerPos;
//
//	if (Vector3::Dot(v, v) <= sphere.radius * sphere.radius)
//		colpara.colFrag = true;
//
//	return colpara;
//}
//
//// カプセルとカプセルの衝突判定
//CollisionParameter Collision::Capsule_vs_Capsule(CollisionParameter & colpara, Capsule & c1, Capsule & c2)
//{
//	int result = HitCheck_Capsule_Capsule(
//		DXConverter::GetInstance().ToVECTOR(c1.startPos),
//		DXConverter::GetInstance().ToVECTOR(c1.endPos),
//		c1.radius,
//		DXConverter::GetInstance().ToVECTOR(c2.startPos),
//		DXConverter::GetInstance().ToVECTOR(c2.endPos),
//		c2.radius);
//
//	if (result > 0)
//		colpara.colFrag = true;
//	else
//		colpara.colFrag = false;
//
//	return colpara;
//}
//
//// OBBと点の最接近点を求める
//void Collision::ClosestPtPointOBB(CollisionParameter & colpara, Vector3 & point, Box & box)
//{
//	Vector3 d = point - box.centerPos;
//	colpara.colPos = box.centerPos;
//
//	for (int i = 0; i < 3; i++)
//	{
//		float dist = Vector3::Dot(d, box.rotate[i]);
//
//		switch (i)
//		{
//		case 0:
//		{
//			if (dist > box.halfSize.x)
//				dist = box.halfSize.x;
//			if (dist < -box.halfSize.x)
//				dist = -box.halfSize.x;
//			colpara.colPos += dist * box.rotate[i];
//			break;
//		}
//		case 1:
//		{
//			if (dist > box.halfSize.y)
//				dist = box.halfSize.y;
//			if (dist < -box.halfSize.y)
//				dist = -box.halfSize.y;
//			colpara.colPos += dist * box.rotate[i];
//			break;
//		}
//		case 2:
//		{
//			if (dist > box.halfSize.z)
//				dist = box.halfSize.z;
//			if (dist < -box.halfSize.z)
//				dist = -box.halfSize.z;
//			colpara.colPos += dist * box.rotate[i];
//			break;
//		}
//		}
//	}
//}




#include "Collision.h"
#include "../Conv/DXConverter.h"
#include <algorithm>

// 球同士の衝突判定
bool Collision::Sphere_Sphere(const Vector3& p1, const float& radius1, const Vector3& p2, const float& radius2){
	return Vector3::Distance(p1, p2) <= radius1 + radius2;
}

// カプセル同士の衝突判定
bool Collision::Capsule_Capsule(const Vector3 p1[], const float& radius1, const Vector3 p2[], const float& radius2) {
	VECTOR p1_start = Vector3::Vector3ToVECTOR(p1[0]);
	VECTOR p1_end = Vector3::Vector3ToVECTOR(p1[1]);
	VECTOR p2_start = Vector3::Vector3ToVECTOR(p2[0]);
	VECTOR p2_end = Vector3::Vector3ToVECTOR(p2[1]);

	//if (HitCheck_Capsule_Capsule(p1_start, p1_end, radius1, p2_start, p2_end, radius2) == TRUE)return true;
	//else return false;

	return HitCheck_Capsule_Capsule(p1_start, p1_end, radius1, p2_start, p2_end, radius2);
}

// カプセル同士の衝突判定
bool Collision::Capsule_Capsule(const Vector3 & pos1, const Matrix & mat1, const float & len1, const float & radius1, const Vector3 & pos2, const Matrix & mat2, const float & len2, const float & radius2)
{
	Vector3 p1[2], p2[2];
	p1[0] = pos1 + Vector3::Up * len1 * mat1;
	p1[1] = pos1 + Vector3::Down * len1 * mat1;
	p2[0] = pos2 + Vector3::Up * len2 * mat2;
	p2[1] = pos2 + Vector3::Down * len2 * mat2;

	return Capsule_Capsule(p1, radius1, p2, radius2);
}

// 線分同士の衝突判定
bool Collision::Segment_Segment(const Vector3 p1[], const Vector3 p2[]){
	VECTOR p1_start = Vector3::Vector3ToVECTOR(p1[0]);
	VECTOR p1_end = Vector3::Vector3ToVECTOR(p1[1]);
	VECTOR p2_start = Vector3::Vector3ToVECTOR(p2[0]);
	VECTOR p2_end = Vector3::Vector3ToVECTOR(p2[1]);

	return Segment_Segment_MinLength_Square(p1_start, p1_end, p2_start, p2_end) < 0;
}

// 線分同士の衝突判定
bool Collision::Segment_Segment(const Vector3 & pos1, const Matrix & mat1, const float & length1, const Vector3 & pos2, const Matrix & mat2, const float & length2){
	Vector3 p1[2], p2[2];
	p1[0] = pos1 + Vector3::Up * length1 * mat1;
	p1[1] = pos1 + Vector3::Down * length1 * mat1;
	p2[0] = pos2 + Vector3::Up * length2 * mat2;
	p2[1] = pos2 + Vector3::Down * length2 * mat2;
	return Segment_Segment(p1, p2);
}

// 球とカプセルの衝突判定
bool Collision::Sphere_Capsule(const Vector3& sphere, const float& sphere_r, const Vector3 capsule[], const float& capsule_r){
	VECTOR sphere_pos = Vector3::Vector3ToVECTOR(sphere);
	VECTOR capsule_start = Vector3::Vector3ToVECTOR(capsule[0]);
	VECTOR capsule_end = Vector3::Vector3ToVECTOR(capsule[1]);

	return Segment_Point_MinLength_Square(capsule_start, capsule_end, sphere_pos) < std::powf(sphere_r + capsule_r, 2);
}

// 球とカプセルの衝突判定
bool Collision::Sphere_Capsule(const Vector3 & sphere, const float & sphere_r, const Vector3 & cap_pos, const Matrix & cap_mat, const float & cap_len, const float & cap_radius)
{
	Vector3 p[2];
	p[0] = cap_pos + Vector3::Up * cap_len * cap_mat;
	p[1] = cap_pos + Vector3::Down * cap_len * cap_mat;

	return Sphere_Capsule(sphere, sphere_r, p, cap_radius);
}

// 球と線分の衝突判定
bool Collision::Sphere_Segment(const Vector3& sphere, const float& sphere_r, const Vector3 & seg_pos, const Matrix & seg_mat, const float & seg_len){
	Vector3 p[2];
	p[0] = seg_pos + Vector3::Up * seg_len * seg_mat;
	p[1] = seg_pos + Vector3::Down * seg_len * seg_mat;

	return Sphere_Segment(sphere, sphere_r, p);
}

// 球と線分の衝突判定
bool Collision::Sphere_Segment(const Vector3& pos, const float& radius, const Vector3 segment[]){
	VECTOR segment_start = Vector3::Vector3ToVECTOR(segment[0]);
	VECTOR segment_end   = Vector3::Vector3ToVECTOR(segment[1]);
	VECTOR sphere_pos = Vector3::Vector3ToVECTOR(pos);
	
	return HitCheck_Line_Sphere(segment_start, segment_end, sphere_pos, radius);
}

// カプセルと線分の衝突判定
bool Collision::Capsule_Segment(const Vector3 capsule[], const float& capsule_r, const Vector3 segment[]){
	VECTOR p1_start = Vector3::Vector3ToVECTOR(capsule[0]);
	VECTOR p1_end = Vector3::Vector3ToVECTOR(capsule[1]);
	VECTOR p2_start = Vector3::Vector3ToVECTOR(segment[0]);
	VECTOR p2_end = Vector3::Vector3ToVECTOR(segment[1]);

	return Segment_Segment_MinLength_Square(p1_start, p1_end, p2_start, p2_end) < std::powf(capsule_r, 2);
}

// カプセルと線分の衝突判定
bool Collision::Capsule_Segment(const Vector3 & seg_pos, const Matrix & seg_mat, const float & seg_len, const Vector3 & cap_pos, const Matrix & cap_mat, const float & cap_len, const float & cap_radius){
	Vector3 p1[2], p2[2];
	p1[0] = cap_pos + Vector3::Up * cap_len * cap_mat;
	p1[1] = cap_pos + Vector3::Down * cap_len * cap_mat;
	p2[0] = seg_pos + Vector3::Up * seg_len * seg_mat;
	p2[1] = seg_pos + Vector3::Down * seg_len * seg_mat;

	return Capsule_Segment(p1, cap_radius, p2);
}

std::vector<MV1_COLL_RESULT_POLY> Collision::Model_Capsule(int modelHandle, const Vector3 & start, const Vector3 & end,float radius)
{
	std::vector<MV1_COLL_RESULT_POLY> colpoly;

	MV1_COLL_RESULT_POLY_DIM HitPolyDim;

	HitPolyDim = MV1CollCheck_Capsule(
		modelHandle, -1,
		start,
		end,
		radius);

	if (HitPolyDim.HitNum != 0)
	{
		for (int i = 0; i < HitPolyDim.HitNum; i++)
		{
			auto angle = Vector3::Dot(Vector3::Up, HitPolyDim.Dim[i].Normal);
			if (MathHelper::Abs(angle) <= 0.5f)
				colpoly.push_back(HitPolyDim.Dim[i]);
		}
	}

	MV1CollResultPolyDimTerminate(HitPolyDim);

	return colpoly;

}

bool Collision::Capsule_Triangle(const Capsule & capsule, const Triangle & poly)
{
	int result = HitCheck_Capsule_Triangle(
		DXConverter::GetInstance().ToVECTOR(capsule.startPos),
		DXConverter::GetInstance().ToVECTOR(capsule.endPos),
		capsule.radius,
		DXConverter::GetInstance().ToVECTOR(poly.position[0]),
		DXConverter::GetInstance().ToVECTOR(poly.position[1]),
		DXConverter::GetInstance().ToVECTOR(poly.position[2]));

	if (result != 0)	return true;
	return false;

}

