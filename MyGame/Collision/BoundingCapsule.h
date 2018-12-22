#pragma once

#include "Base/Body.h"

// カプセル
class BoundingCapsule : public Body {
public:
	//カプセルの判定を作成
	BoundingCapsule(const Vector3& pos, const Matrix& mat, const float& len, const float& rad);
public:
	// 衝突判定
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const override;
	// 衝突判定(球)
	virtual bool intersects(const BoundingSphere& other, HitInfo& hitinfo) const override;
	// 衝突判定(カプセル)
	virtual bool intersects(const BoundingCapsule& other, HitInfo& hitinfo) const override;
	// 衝突判定(線分)
	virtual bool intersects(const BoundingSegment& other, HitInfo& hitinfo) const override;
	// 衝突判定(AABB)
	virtual bool intersects(const BoundingBox& other, HitInfo& hitinfo) const override;
	// 衝突判定(OBB)
	virtual bool intersects(const OrientedBoundingBox& other, HitInfo& hitinfo) const override;
	// 衝突判定(レイ)
	virtual bool intersects(const Ray& other, HitInfo& hitinfo) const override;
	// 衝突判定(モデル)
	virtual bool intersects(const CollisionModel& other, HitInfo& hitinfo) const override;

	// Bodyの平行移動
	virtual IBodyPtr translate(const Vector3& pos) const override;
	// Bodyの変換
	virtual IBodyPtr transform(const Matrix& mat) const override;

	// Bodyの平行移動
	BoundingCapsule translate_e(const Vector3& pos) const;
	// Bodyの変換
	BoundingCapsule transform_e(const Matrix& mat) const;

	// 図形描画
	virtual void draw() const override;
	virtual void draw(const Vector3& position) const override;
};