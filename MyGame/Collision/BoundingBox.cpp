#include "BoundingBox.h"
#include "OrientedBoundingBox.h"
#include "BoundingSphere.h"
#include "BoundingCapsule.h"
#include "BoundingSegment.h"
#include "Ray.h"
#include "CollisionModel.h"

#include <cmath>
#include <algorithm>
#include <limits>

#include "Base/HitInfo.h"
#include "Collision.h"

//AABBの判定を作成
BoundingBox::BoundingBox(const Vector3 & min, const Vector3 & max) :
	Body(ShapeType::AABB, (max + min) / 2.0f, min, max){}

// 衝突判定
bool BoundingBox::isCollide(const IBody & other, HitInfo & hitinfo) const {
	// どちらかの判定を行わない場合false
	if (!other.enabled() || !enabled())return false;

	return other.intersects(*this, hitinfo);
}

// 衝突判定(球)
bool BoundingBox::intersects(const BoundingSphere & sphere, HitInfo & hitinfo) const{
	const Vector3 point = ClosestPoint(sphere.position());
	hitinfo.intersect = point;
	return sphere.contains(point);
}

// 衝突判定(カプセル)
bool BoundingBox::intersects(const BoundingCapsule & capsule, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(線分)
bool BoundingBox::intersects(const BoundingSegment & segment, HitInfo & hitinfo) const{
	float near_ = 0.0f;
	float far_ = segment.length();
	const Vector3 direction = segment.Direction();
	const bool result = intersects(segment.points(0), direction, near_, far_);
	if (result) {
		hitinfo.intersect = segment.points(0) + direction * near_;
	}
	return result;
}

// 衝突判定(AABB)
bool BoundingBox::intersects(const BoundingBox & aabb, HitInfo & hitinfo) const{
	return	mMin.x < aabb.mMax.x && mMin.y < aabb.mMax.y && mMin.z < aabb.mMax.z &&
			aabb.mMin.x < mMax.x && aabb.mMin.y < mMax.y && aabb.mMin.z < mMax.z;
}

// 衝突判定(OBB)
bool BoundingBox::intersects(const OrientedBoundingBox & obb, HitInfo & hitinfo) const{
	return obb.intersects(*this, hitinfo);
}

// 衝突判定(レイ)
bool BoundingBox::intersects(const Ray & ray, HitInfo & hitinfo) const{
	float start = 0.0f;
	float end = 0.00001f;// std::numeric_limits<float>::max();
	const bool result = intersects(ray.position(), ray.direction(), start, end);
	if (result) {
		hitinfo.intersect = ray.position() + ray.direction() * start;
	}
	return result;
}

// 衝突判定(モデル)
bool BoundingBox::intersects(const CollisionModel & other, HitInfo & hitinfo) const{
	return false;
}

// 包含判定(点)
bool BoundingBox::contains(const Vector3 & point) const{
	return	(mMin.x <= point.x && point.x <= mMax.x) &&
			(mMin.y <= point.y && point.y <= mMax.y) &&
			(mMin.z <= point.z && point.z <= mMax.z);
}

// 包含判定(球)
bool BoundingBox::contains(const BoundingSphere & sphere) const{
	const Vector3 offset(sphere.radius(), sphere.radius(), sphere.radius());
	return contains(BoundingBox(sphere.position() - offset, sphere.position() + offset));
}

// 包含判定(線分)
bool BoundingBox::contains(const BoundingSegment & segment) const{
	return contains(segment.points(0)) && contains(segment.points(1));
}

// 包含判定(AABB)
bool BoundingBox::contains(const BoundingBox & aabb) const{
	return	(mMin.x <= aabb.mMin.x && aabb.mMax.x <= mMax.x) &&
			(mMin.y <= aabb.mMin.y && aabb.mMax.y <= mMax.y) &&
			(mMin.z <= aabb.mMin.z && aabb.mMax.z <= mMax.z);
}

// 包含判定(OBB)
bool BoundingBox::contains(const OrientedBoundingBox & obb) const{
	return false;
}

// Bodyの平行移動
IBodyPtr BoundingBox::translate(const Vector3 & pos) const{
	return std::make_shared<BoundingBox>(translate_e(pos));
}

// Bodyの変換
IBodyPtr BoundingBox::transform(const Matrix & mat) const{
	return std::make_shared<BoundingBox>(transform_e(mat));
}

// Bodyの平行移動
BoundingBox BoundingBox::translate_e(const Vector3 & pos) const{
	return BoundingBox(mMin + pos, mMax + pos);
}

// Bodyの変換
BoundingBox BoundingBox::transform_e(const Matrix & mat) const{
	return BoundingBox(mMin, mMax);
}

// 線の衝突判定
bool BoundingBox::intersects(const Vector3 & position, const Vector3 & direction, float & start, float & end) const{
	//xスラブ
	if (std::abs(direction.x) > std::numeric_limits<float>::epsilon()) {
		const float t1 = (mMin.x - position.x) / direction.x;
		const float t2 = (mMax.x - position.x) / direction.x;
		if (t1 < t2) {
			start = std::max<float>(t1, start);
			end = std::min<float>(t2, end);
		}
		else {
			start = std::max<float>(t2, start);
			end = std::min<float>(t1, end);
		}
		if (start > end) {
			return false;
		}
	}
	else if (position.x < mMin.x || position.x > mMax.x) {
		return false;
	}
	//yスラブ
	if (std::abs(direction.y) > std::numeric_limits<float>::epsilon()) {
		const float t1 = (mMin.y - position.y) / direction.y;
		const float t2 = (mMax.y - position.y) / direction.y;
		if (t1 < t2) {
			start = std::max<float>(t1, start);
			end = std::min<float>(t2, end);
		}
		else {
			start = std::max<float>(t2, start);
			end = std::min<float>(t1, end);
		}
		if (start > end) {
			return false;
		}
	}
	else if (position.y < mMin.y || position.y > mMax.y) {
		return false;
	}
	//zスラブ
	if (std::abs(direction.z) > std::numeric_limits<float>::epsilon()) {
		const float t1 = (mMin.z - position.z) / direction.z;
		const float t2 = (mMax.z - position.z) / direction.z;
		if (t1 < t2) {
			start = std::max<float>(t1, start);
			end = std::min<float>(t2, end);
		}
		else {
			start = std::max<float>(t2, start);
			end = std::min<float>(t1, end);
		}
		if (start > end) {
			return false;
		}
	}
	else if (position.z < mMin.z || position.z > mMax.z) {
		return false;
	}
	return true;
}

// 近接点
Vector3 BoundingBox::ClosestPoint(const Vector3 & target) const{
	return Vector3::Clamp(target, mMin, mMax);
}

// 頂点
Vector3 BoundingBox::CornerPoint(int cornerIndex) const{
	switch (cornerIndex) {
	default:
	case 0: return mMin;
	case 1: return Vector3(mMin.x, mMin.y, mMax.z);
	case 2: return Vector3(mMin.x, mMax.y, mMin.z);
	case 3: return Vector3(mMin.x, mMax.y, mMax.z);
	case 4: return Vector3(mMax.x, mMin.y, mMin.z);
	case 5: return Vector3(mMax.x, mMin.y, mMax.z);
	case 6: return Vector3(mMax.x, mMax.y, mMin.z);
	case 7: return mMax;
	}
}

// 矩形のサイズ
Vector3 BoundingBox::Size() const{
	return mMax - mMin;
}

// 中心座標
Vector3 BoundingBox::Center() const{
	return (mMax + mMin) / 2.0f;
}

// 図形描画
void BoundingBox::draw() const{
}

void BoundingBox::draw(const Vector3 & position) const
{
}
