#pragma once

#include "Base/Body.h"

// モデル
class CollisionModel : public Body {
public:
	// コンストラクタ
	CollisionModel() {}
public:
	// 衝突判定
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const override { return false; }
	// 衝突判定(球)
	virtual bool intersects(const BoundingSphere& other, HitInfo& hitinfo) const override { return false; }
	// 衝突判定(カプセル)
	virtual bool intersects(const BoundingCapsule& other, HitInfo& hitinfo) const override { return false; }
	// 衝突判定(線分)
	virtual bool intersects(const BoundingSegment& other, HitInfo& hitinfo) const override { return false; }
	// 衝突判定(AABB)
	virtual bool intersects(const BoundingBox& other, HitInfo& hitinfo) const override { return false; }
	// 衝突判定(OBB)
	virtual bool intersects(const OrientedBoundingBox& other, HitInfo& hitinfo) const override { return false; }
	// 衝突判定(レイ)
	virtual bool intersects(const Ray& other, HitInfo& hitinfo) const override { return false; }
	// 衝突判定(モデル)
	virtual bool intersects(const CollisionModel& other, HitInfo& hitinfo) const override { return false; }
	// Bodyの平行移動
	virtual IBodyPtr translate(const Vector3& pos) const override {}
	// Bodyの変換
	virtual IBodyPtr transform(const Matrix& mat) const override {}
	// 図形描画
	virtual void draw() const override {}
	virtual void draw(const Vector3& position) const override{}
};


