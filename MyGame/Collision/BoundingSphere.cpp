#include "BoundingSphere.h"
#include "BoundingCapsule.h"
#include "BoundingSegment.h"
#include "BoundingBox.h"
#include "OrientedBoundingBox.h"
#include "Ray.h"
#include "CollisionModel.h"

#include "Collision.h"

//球の判定を作成する
BoundingSphere::BoundingSphere(const Vector3& pos, const float& rad) :
	Body(ShapeType::Sphere, pos, rad) {
}

// 衝突判定
bool BoundingSphere::isCollide(const IBody & other, HitInfo & hitinfo) const {
	// どちらかの判定を行わない場合false
	if (!other.enabled() || !enabled())return false;

	return other.intersects(*this, hitinfo);
}

// 衝突判定(球)
bool BoundingSphere::intersects(const BoundingSphere & other, HitInfo & hitinfo) const {
	return Collision::Sphere_Sphere(mPosition, mRadius, other.mPosition, other.mRadius);
}

// 衝突判定(カプセル)
bool BoundingSphere::intersects(const BoundingCapsule & other, HitInfo & hitinfo) const {
	return Collision::Sphere_Capsule(mPosition, mRadius, other.position(), other.matrix(), other.length(), other.radius());
}

// 衝突判定(線分)
bool BoundingSphere::intersects(const BoundingSegment & other, HitInfo & hitinfo) const {
	return Collision::Sphere_Segment(mPosition, mRadius, other.position(), other.matrix(), other.length());
}

// 衝突判定(AABB)
bool BoundingSphere::intersects(const BoundingBox & other, HitInfo & hitinfo) const {
	return false;
}

// 衝突判定(OBB)
bool BoundingSphere::intersects(const OrientedBoundingBox & other, HitInfo & hitinfo) const {
	return false;
}

// 衝突判定(レイ)
bool BoundingSphere::intersects(const Ray & other, HitInfo & hitinfo) const {
	return false;
}

// 衝突判定(モデル)
bool BoundingSphere::intersects(const CollisionModel & other, HitInfo & hitinfo) const {
	return false;
}

// 包含判定(点)
bool BoundingSphere::contains(const Vector3 & point) const {
	return Vector3::DistanceSquared(mPosition, point) <= mRadius * mRadius;
}

// 包含判定(球)
bool BoundingSphere::contains(const BoundingSphere & sphere) const {
	return Vector3::DistanceSquared(mPosition, sphere.position()) + sphere.radius() <= mRadius;
}

// Bodyの平行移動
IBodyPtr BoundingSphere::translate(const Vector3 & pos) const {
	return std::make_shared<BoundingSphere>(translate_e(pos));
}

// Bodyの変換
IBodyPtr BoundingSphere::transform(const Matrix & mat) const {
	return std::make_shared<BoundingSphere>(transform_e(mat));
}

// Bodyの平行移動
BoundingSphere BoundingSphere::translate_e(const Vector3 & pos) const {
	return BoundingSphere(mPosition + pos, mRadius);
}

// Bodyの変換
BoundingSphere BoundingSphere::transform_e(const Matrix & mat) const {
	return BoundingSphere(mPosition + mat.Translation(), mRadius * mat.Scale().y);
}

// 図形描画
void BoundingSphere::draw() const {
#ifdef _DEBUG
	DrawSphere3D(mPosition, mRadius, 32, GetColor(255, 0, 0), GetColor(125, 125, 125), FALSE);
#endif // _DEBUG
}

void BoundingSphere::draw(const Vector3 & position) const
{
}

