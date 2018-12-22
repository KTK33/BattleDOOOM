#include "OrientedBoundingBox.h"
#include "BoundingSphere.h"
#include "BoundingCapsule.h"
#include "BoundingSegment.h"
#include "BoundingBox.h"
#include "Ray.h"
#include "CollisionModel.h"

#include "Base/HitInfo.h"
#include "Collision.h"

static const float EPSILON = 1e-3f;

//OBBの判定を作成
OrientedBoundingBox::OrientedBoundingBox(const Vector3 & position, const Vector3 & extents, const Vector3 & axis_x, const Vector3 & axis_y, const Vector3 & axis_z) :
	Body(ShapeType::OBB, position, extents){
	mAxis[0] = axis_x;
	mAxis[1] = axis_y;
	mAxis[2] = axis_z;
}

//OBBの判定を作成(aabbを利用)
OrientedBoundingBox::OrientedBoundingBox(const BoundingBox & aabb) :
	Body(ShapeType::OBB, (aabb.box_min() + aabb.box_max()) / 2.0f, (aabb.box_max() - aabb.box_min()) / 2.0f) {
	mAxis[0] = Vector3(1.0f, 0.0f, 0.0f);
	mAxis[1] = Vector3(0.0f, 1.0f, 0.0f);
	mAxis[2] = Vector3(0.0f, 0.0f, 1.0f);
}

// 衝突判定
bool OrientedBoundingBox::isCollide(const IBody & other, HitInfo & hitinfo) const{
	// どちらかの判定を行わない場合false
	if (!other.enabled() || !enabled())return false;
	
	//ここをActorで呼んでまとめている
	//相手側のintersectsを呼ぶことで、此方の型を自動決定してくれる:ダブルディスパッチ
	//HitInfoは、欲しい情報を適宜追加していく
	return other.intersects(*this, hitinfo);
}

// 衝突判定(球)
bool OrientedBoundingBox::intersects(const BoundingSphere & other, HitInfo & hitinfo) const{
	Vector3 closest_point = ClosestPoint(other.position());
	hitinfo.intersect = closest_point;
	return other.contains(closest_point);
}

// 衝突判定(カプセル)
bool OrientedBoundingBox::intersects(const BoundingCapsule & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(線分)
bool OrientedBoundingBox::intersects(const BoundingSegment & other, HitInfo & hitinfo) const{
	BoundingBox aabb(-mExtents, mExtents);
	const bool result = aabb.intersects(other.transform_e(WorldToLocal()), hitinfo);
	if (result) {
		hitinfo.intersect = Vector3::Transform(hitinfo.intersect, LocalToWorld());
	}
	return result;
}

// 衝突判定(AABB)
bool OrientedBoundingBox::intersects(const BoundingBox & other, HitInfo & hitinfo) const{
	return intersects(OrientedBoundingBox(other), hitinfo);
}

// 衝突判定(OBB)
bool OrientedBoundingBox::intersects(const OrientedBoundingBox & other, HitInfo & hitinfo) const{
	Matrix R;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			R.m[i][j] = Vector3::Dot(mAxis[i], other.mAxis[j]);
		}
	}
	Matrix AbsR;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			AbsR.m[i][j] = std::abs(R.m[i][j]) + EPSILON;
		}
	}
	const float ae[3] = { mExtents.x, mExtents.y, mExtents.z };
	const float be[3] = { other.mExtents.x, other.mExtents.y, other.mExtents.z };
	float ra = 0.0f, rb = 0.0f;

	Vector3 tmp = other.mPosition - mPosition;
	float t[3] = { Vector3::Dot(tmp, mAxis[0]),Vector3::Dot(tmp, mAxis[1]),Vector3::Dot(tmp, mAxis[2]) };
	for (int i = 0; i < 3; ++i) {
		ra = ae[i];
		rb = be[0] * AbsR.m[i][0] + be[1] * AbsR.m[i][1] + be[2] * AbsR.m[i][2];
		if (std::abs(t[i]) > ra + rb) {
			return false;
		}
	}

	for (int i = 0; i < 3; ++i) {
		rb = ae[0] * AbsR.m[0][i] + ae[1] * AbsR.m[1][i] + ae[2] * AbsR.m[2][i];
		ra = be[i];
		if (std::abs(t[0] * R.m[0][i] + t[1] * R.m[1][i] + t[2] * R.m[2][i]) > ra + rb) {
			return false;
		}
	}

	ra = ae[2] * AbsR.m[2][0] + ae[2] * AbsR.m[1][0];
	rb = be[2] * AbsR.m[0][2] + be[2] * AbsR.m[0][1];
	if (std::abs(t[0] * R.m[1][0] - t[1] * R.m[2][0]) > ra + rb)return false;

	ra = ae[2] * AbsR.m[2][1] + ae[2] * AbsR.m[1][1];
	rb = be[0] * AbsR.m[0][2] + be[2] * AbsR.m[0][0];
	if (std::abs(t[2] * R.m[1][1] - t[1] * R.m[2][1]) > ra + rb)return false;

	ra = ae[1] * AbsR.m[2][2] + ae[2] * AbsR.m[1][2];
	rb = be[0] * AbsR.m[0][1] + be[2] * AbsR.m[0][0];
	if (std::abs(t[2] * R.m[1][2] - t[1] * R.m[2][2]) > ra + rb)return false;

	ra = ae[0] * AbsR.m[2][0] + ae[2] * AbsR.m[0][0];
	rb = be[2] * AbsR.m[1][2] + be[2] * AbsR.m[1][1];
	if (std::abs(t[0] * R.m[2][0] - t[2] * R.m[0][0]) > ra + rb)return false;

	ra = ae[0] * AbsR.m[2][1] + ae[2] * AbsR.m[0][1];
	rb = be[0] * AbsR.m[1][2] + be[2] * AbsR.m[1][0];
	if (std::abs(t[0] * R.m[2][1] - t[2] * R.m[0][1]) > ra + rb)return false;

	ra = ae[0] * AbsR.m[2][2] + ae[2] * AbsR.m[0][2];
	rb = be[0] * AbsR.m[1][1] + be[2] * AbsR.m[1][0];
	if (std::abs(t[0] * R.m[2][2] - t[2] * R.m[0][2]) > ra + rb)return false;

	ra = ae[0] * AbsR.m[1][0] + ae[1] * AbsR.m[0][0];
	rb = be[1] * AbsR.m[2][2] + be[2] * AbsR.m[2][1];
	if (std::abs(t[1] * R.m[0][0] - t[0] * R.m[1][0]) > ra + rb)return false;

	ra = ae[0] * AbsR.m[1][1] + ae[1] * AbsR.m[0][1];
	rb = be[0] * AbsR.m[2][2] + be[2] * AbsR.m[2][0];
	if (std::abs(t[1] * R.m[0][1] - t[0] * R.m[1][1]) > ra + rb)return false;

	ra = ae[0] * AbsR.m[1][2] + ae[1] * AbsR.m[0][2];
	rb = be[0] * AbsR.m[2][1] + be[1] * AbsR.m[2][0];
	if (std::abs(t[1] * R.m[0][2] - t[0] * R.m[1][2]) > ra + rb)return false;

	return true;
}

// 衝突判定(レイ)
bool OrientedBoundingBox::intersects(const Ray & other, HitInfo & hitinfo) const{
	BoundingBox aabb(-mExtents, mExtents);
	const bool result = aabb.intersects(other.transform_e(WorldToLocal()), hitinfo);
	if (result) {
		hitinfo.intersect = Vector3::Transform(hitinfo.intersect, LocalToWorld());
	}
	return result;
}

// 衝突判定(モデル)
bool OrientedBoundingBox::intersects(const CollisionModel & other, HitInfo & hitinfo) const{
	return false;
}

// 包含判定(点)
bool OrientedBoundingBox::contains(const Vector3 & point) const{
	const Vector3 pt = point - mPosition;
	return	std::abs(Vector3::Dot(pt, mAxis[0])) <= mExtents.x &&
			std::abs(Vector3::Dot(pt, mAxis[1])) <= mExtents.y &&
			std::abs(Vector3::Dot(pt, mAxis[2])) <= mExtents.z;
}

// 包含判定(球)
bool OrientedBoundingBox::contains(const BoundingSphere & sphere) const{
	return BoundingBox(-mExtents, mExtents).contains(sphere.transform_e(WorldToLocal()));
}

// 包含判定(線分)
bool OrientedBoundingBox::contains(const BoundingSegment & segment) const{
	return contains(segment.points(0)) && contains(segment.points(1));
}

// 包含判定(AABB)
bool OrientedBoundingBox::contains(const BoundingBox & aabb) const{
	for (int i = 0; i < 8; ++i) {
		if (!contains(aabb.CornerPoint(i))) return false;
	}
	return true;
}

// 包含判定(OBB)
bool OrientedBoundingBox::contains(const OrientedBoundingBox & obb) const{
	for (int i = 0; i < 8; ++i) {
		if (!contains(obb.CornerPoint(i))) return false;
	}
	return true;
}

// Bodyの平行移動
IBodyPtr OrientedBoundingBox::translate(const Vector3 & pos) const {
	return std::make_shared<OrientedBoundingBox>(translate_e(pos));
}

// Bodyの変換
IBodyPtr OrientedBoundingBox::transform(const Matrix & mat) const {
	return std::make_shared<OrientedBoundingBox>(transform_e(mat));
}

// Bodyの平行移動
OrientedBoundingBox OrientedBoundingBox::translate_e(const Vector3 & pos) const{
	return OrientedBoundingBox(mPosition + pos, mExtents, mAxis[0], mAxis[1], mAxis[2]);
}

// Bodyの変換
OrientedBoundingBox OrientedBoundingBox::transform_e(const Matrix & mat) const{
	const Vector3 scale = mat.Scale();
	return OrientedBoundingBox(
		Vector3::Transform(mPosition, mat),
		Vector3(mExtents.x * scale.x, mExtents.y * scale.y, mExtents.z * scale.z),
		Vector3::Normalize(Vector3::TransformNormal(mAxis[0], mat)),
		Vector3::Normalize(Vector3::TransformNormal(mAxis[1], mat)),
		Vector3::Normalize(Vector3::TransformNormal(mAxis[2], mat))
		);
}

// 近接点
Vector3 OrientedBoundingBox::ClosestPoint(const Vector3 & target) const{
	const Vector3& d = target - mPosition;
	Vector3 result = mPosition;
	result += MathHelper::Clamp(Vector3::Dot(d, mAxis[0]), -mExtents.x, mExtents.x) * mAxis[0];
	result += MathHelper::Clamp(Vector3::Dot(d, mAxis[1]), -mExtents.y, mExtents.y) * mAxis[1];
	result += MathHelper::Clamp(Vector3::Dot(d, mAxis[2]), -mExtents.z, mExtents.z) * mAxis[2];
	return result;
}

// 頂点
Vector3 OrientedBoundingBox::CornerPoint(int cornerIndex) const {
	switch (cornerIndex) {
	default:
	case 0: return mPosition - mExtents.x * mAxis[0] - mExtents.y * mAxis[1] - mExtents.z * mAxis[2];
	case 1: return mPosition - mExtents.x * mAxis[0] - mExtents.y * mAxis[1] + mExtents.z * mAxis[2];
	case 2: return mPosition - mExtents.x * mAxis[0] + mExtents.y * mAxis[1] - mExtents.z * mAxis[2];
	case 3: return mPosition - mExtents.x * mAxis[0] + mExtents.y * mAxis[1] + mExtents.z * mAxis[2];
	case 4: return mPosition + mExtents.x * mAxis[0] - mExtents.y * mAxis[1] - mExtents.z * mAxis[2];
	case 5: return mPosition + mExtents.x * mAxis[0] - mExtents.y * mAxis[1] + mExtents.z * mAxis[2];
	case 6: return mPosition + mExtents.x * mAxis[0] + mExtents.y * mAxis[1] - mExtents.z * mAxis[2];
	case 7: return mPosition + mExtents.x * mAxis[0] + mExtents.y * mAxis[1] + mExtents.z * mAxis[2];
	}
}

// 矩形のサイズ
Vector3 OrientedBoundingBox::Size() const{
	return mExtents * 2.0f;
}

// 中心座標
Vector3 OrientedBoundingBox::Center() const{
	return mPosition;
}

// ローカル座標へ変換
Matrix OrientedBoundingBox::LocalToWorld() const {
	return Matrix(
		mAxis[0].x, mAxis[0].y, mAxis[0].z, 0.0f,
		mAxis[1].x, mAxis[1].y, mAxis[1].z, 0.0f,
		mAxis[2].x, mAxis[2].y, mAxis[2].z, 0.0f,
		mPosition.x, mPosition.y, mPosition.z, 1.0f
		);
}

// ワールド座標へ変換
Matrix OrientedBoundingBox::WorldToLocal() const {
	return Matrix::InvertFast(LocalToWorld());
}

// 図形描画
void OrientedBoundingBox::draw() const{
}

void OrientedBoundingBox::draw(const Vector3 & position) const
{
}
