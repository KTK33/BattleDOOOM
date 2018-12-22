#pragma once

#include "IBodyPtr.h"

#include "ShapeType.h"

struct Vector3;
struct Matrix;
struct HitInfo;

class BoundingSphere;
class BoundingCapsule;
class BoundingSegment;
class BoundingBox;
class OrientedBoundingBox;
class Ray;
class CollisionModel;

// Bodyインターフェースクラス
class IBody{
public:
	// コンストラクタ
	IBody() {}
	// デストラクタ
	virtual ~IBody() = default;
public:
	// Bodyの平行移動
	virtual IBodyPtr translate(const Vector3& position) const = 0;
	// Bodyの変換
	virtual IBodyPtr transform(const Matrix& matrix) const = 0;
	// 衝突判定
	virtual bool isCollide(const IBody& other, HitInfo& hitinfo) const = 0;
	// 衝突判定(球)
	virtual bool intersects(const BoundingSphere& other, HitInfo& hitinfo) const = 0;
	// 衝突判定(カプセル)
	virtual bool intersects(const BoundingCapsule& other, HitInfo& hitinfo) const = 0;
	// 衝突判定(線分)
	virtual bool intersects(const BoundingSegment& other, HitInfo& hitinfo) const = 0;
	// 衝突判定(AABB)
	virtual bool intersects(const BoundingBox& other, HitInfo& hitinfo) const = 0;
	// 衝突判定(OBB)
	virtual bool intersects(const OrientedBoundingBox& other, HitInfo& hitinfo) const = 0;
	// 衝突判定(レイ)
	virtual bool intersects(const Ray& other, HitInfo& hitinfo) const = 0;
	// 衝突判定(モデル)
	virtual bool intersects(const CollisionModel& other, HitInfo& hitinfo) const = 0;

	virtual bool contains(const Vector3& point) const { return false; }

	virtual bool contains(const BoundingSphere& sphere) const { return false; }

	virtual bool contains(const BoundingSegment& segment) const { return false; }

	virtual bool contains(const BoundingBox& aabb) const { return false; }

	virtual bool contains(const OrientedBoundingBox& obb) const { return false; }
	// 判定のON、OFF
	virtual void active(bool active) = 0;
	// 判定があるかどうか
	virtual bool enabled() const = 0;
	// 図形描画
	virtual void draw() const = 0;
	virtual void draw(const Vector3& position) const = 0;
	// 形状の取得
	virtual ShapeType type() const = 0;
	// 中心座標の取得
	virtual Vector3 position() const = 0;
	// 変換行列の取得
	virtual Matrix matrix() const = 0;
	// 半径の取得
	virtual float radius() const = 0;
	// 長さの取得
	virtual float length() const = 0;
	// 方向の取得
	virtual Vector3 direction() const = 0;
	// 縦幅の取得
	virtual float height() const = 0;
	// 横幅の取得
	virtual float width() const = 0;
	// 奥行の取得
	virtual float depth() const = 0;
	// 矩形の最小点の取得
	virtual Vector3 box_min() const = 0;
	// 矩形の最大点の取得
	virtual Vector3 box_max() const = 0;
	// 矩形の大きさの取得
	virtual Vector3 extents() const = 0;
	// 矩形の軸の取得
	virtual Vector3 axis(const int index) const = 0;
	// 点の取得
	virtual Vector3 points(const int index) const = 0;
};

