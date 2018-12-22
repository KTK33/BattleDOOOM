#include "Ray.h"

// コンストラクタ
Ray::Ray(const Vector3 & position, const Vector3 & direction) :
	Body(ShapeType::Ray, position, Matrix::Identity, direction){}

// 衝突判定
bool Ray::isCollide(const IBody & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(球)
bool Ray::intersects(const BoundingSphere & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(カプセル)
bool Ray::intersects(const BoundingCapsule & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(線分)
bool Ray::intersects(const BoundingSegment & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(AABB)
bool Ray::intersects(const BoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(OBB)
bool Ray::intersects(const OrientedBoundingBox & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(レイ)
bool Ray::intersects(const Ray & other, HitInfo & hitinfo) const{
	return false;
}

// 衝突判定(モデル)
bool Ray::intersects(const CollisionModel & other, HitInfo & hitinfo) const{
	return false;
}

// Bodyの平行移動
IBodyPtr Ray::translate(const Vector3 & pos) const {
	return std::make_shared<Ray>(translate_e(pos));
}

// Bodyの変換
IBodyPtr Ray::transform(const Matrix & mat) const {
	return std::make_shared<Ray>(transform_e(mat));
}

// Bodyの平行移動
Ray Ray::translate_e(const Vector3 & pos) const {
	return Ray(mPosition + pos, mDirection);
}

// Bodyの変換
Ray Ray::transform_e(const Matrix & mat) const {
	return Ray(mPosition * mat, mDirection);
}

// 図形描画
void Ray::draw() const{}

void Ray::draw(const Vector3 & position) const
{
}
