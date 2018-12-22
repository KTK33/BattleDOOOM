#pragma once

#include "Base/Body.h"

// AABB
class BoundingBox : public Body {
public:
	//AABBの判定を作成
	BoundingBox(const Vector3& min, const Vector3& max);
public:
	// 衝突判定
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const override;
	// 衝突判定(球)
	virtual bool intersects(const BoundingSphere& sphere, HitInfo& hitinfo) const override;
	// 衝突判定(カプセル)
	virtual bool intersects(const BoundingCapsule& capsule, HitInfo& hitinfo) const override;
	// 衝突判定(線分)
	virtual bool intersects(const BoundingSegment& segment, HitInfo& hitinfo) const override;
	// 衝突判定(AABB)
	virtual bool intersects(const BoundingBox& aabb, HitInfo& hitinfo) const override;
	// 衝突判定(OBB)
	virtual bool intersects(const OrientedBoundingBox& obb, HitInfo& hitinfo) const override;
	// 衝突判定(レイ)
	virtual bool intersects(const Ray& ray, HitInfo& hitinfo) const override;
	// 衝突判定(モデル)
	virtual bool intersects(const CollisionModel& model, HitInfo& hitinfo) const override;
	
	// 包含判定(点)
	virtual bool contains(const Vector3& point) const override;
	// 包含判定(球)
	virtual bool contains(const BoundingSphere& sphere) const override;
	// 包含判定(線分)
	virtual bool contains(const BoundingSegment& segment) const override;
	// 包含判定(AABB)
	virtual bool contains(const BoundingBox& aabb) const override;
	// 包含判定(OBB)
	virtual bool contains(const OrientedBoundingBox& obb) const override;

	// Bodyの平行移動
	virtual IBodyPtr translate(const Vector3& pos) const override;
	// Bodyの変換
	virtual IBodyPtr transform(const Matrix& mat) const override;

	// Bodyの平行移動
	BoundingBox translate_e(const Vector3& pos) const;
	// Bodyの変換
	BoundingBox transform_e(const Matrix& mat) const;

	// 線の衝突判定
	bool intersects(const Vector3& position, const Vector3& direction, float& start, float& end) const;
	// 近接点
	Vector3 ClosestPoint(const Vector3& target)const;
	// 頂点
	Vector3 CornerPoint(int cornerIndex)const;
	// 矩形のサイズ
	Vector3 Size()const;
	// 中心座標
	Vector3 Center()const;

	// 図形描画
	virtual void draw() const override;
	virtual void draw(const Vector3& position) const override;
};
