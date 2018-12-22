#include "BoundingSphere.h"
#include "BoundingCapsule.h"
#include "BoundingSegment.h"
#include "BoundingBox.h"
#include "OrientedBoundingBox.h"
#include "Ray.h"
#include "CollisionModel.h"

#include "Collision.h"

// コンストラクタ
BoundingSegment::BoundingSegment(const Vector3 & pos, const Matrix & mat, const float& len):
	Body(ShapeType::Segment, pos, mat, len, true) {
	mPoints[0] = pos + Vector3::Up * len / 2;
	mPoints[1] = pos - Vector3::Up * len / 2;
}

// 衝突判定
bool BoundingSegment::isCollide(const IBody & other, HitInfo & hitinfo) const {
	// どちらかの判定を行わない場合false
	if (!other.enabled() || !enabled())return false;
	
	return other.intersects(*this, hitinfo);
}

// 衝突判定(球)
bool BoundingSegment::intersects(const BoundingSphere & other, HitInfo & hitinfo) const{
	return Collision::Sphere_Segment(other.position(), other.radius(), mPosition, mMatrix, mLength);
}

// 衝突判定(カプセル)
bool BoundingSegment::intersects(const BoundingCapsule & other, HitInfo & hitinfo) const{
	return Collision::Capsule_Segment(mPosition, mMatrix, mLength, other.position(), other.matrix(), other.length(), other.radius());
}

// 衝突判定(線分)
bool BoundingSegment::intersects(const BoundingSegment & other, HitInfo & hitinfo) const{
	return Collision::Segment_Segment(mPosition, mMatrix, mLength, other.mPosition, other.matrix(), other.length());
}

// 衝突判定(AABB)
bool BoundingSegment::intersects(const BoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(OBB)
bool BoundingSegment::intersects(const OrientedBoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(レイ)
bool BoundingSegment::intersects(const Ray & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(モデル)
bool BoundingSegment::intersects(const CollisionModel & other, HitInfo & hitinfo) const{
	return false;
}

// Bodyの平行移動
IBodyPtr BoundingSegment::translate(const Vector3 & pos) const{
	return std::make_shared<BoundingSegment>(translate_e(pos));
}

// Bodyの変換
IBodyPtr BoundingSegment::transform(const Matrix & mat) const{
	return std::make_shared<BoundingSegment>(transform_e(mat));
}

// Bodyの平行移動
BoundingSegment BoundingSegment::translate_e(const Vector3 & pos) const{
	return BoundingSegment(mPosition + pos, mMatrix, mLength);
}

// Bodyの変換
BoundingSegment BoundingSegment::transform_e(const Matrix & mat) const{
	return BoundingSegment(mPosition + mat.Translation(), mMatrix * mat.RotationMatrix(), mLength * mat.Scale().y);
}

// 始点から終点への方向を返す
Vector3 BoundingSegment::Direction() const{
	Vector3 p[2];
	p[0] = mPosition + Vector3::Up * mLength / 2 * mMatrix;
	p[1] = mPosition + Vector3::Down * mLength / 2 * mMatrix;

	return Vector3::Normalize(p[0] - p[1]);
}

// 図形描画
void BoundingSegment::draw() const{
#ifdef _DEBUG

	Vector3 p[2];
	p[0] = mPosition + Vector3::Up * mLength / 2 * mMatrix;
	p[1] = mPosition + Vector3::Down * mLength / 2 * mMatrix;

	DrawLine3D(Vector3::Vector3ToVECTOR(p[0]), Vector3::Vector3ToVECTOR(p[1]), GetColor(255, 255, 255));
#endif // _DEBUG
}

void BoundingSegment::draw(const Vector3 & position) const
{
#ifdef _DEBUG


	Vector3 p[2];
	p[0] = mPosition + Vector3::Up * mLength / 2 * mMatrix +position;
	p[1] = mPosition + Vector3::Down * mLength / 2 * mMatrix +position;

	DrawLine3D(Vector3::Vector3ToVECTOR(p[0]), Vector3::Vector3ToVECTOR(p[1]), GetColor(255, 255, 255));

#endif // _DEBUG
}

