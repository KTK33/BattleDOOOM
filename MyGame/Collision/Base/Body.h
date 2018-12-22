#pragma once

#include "IBody.h"
#include "../../Math/MathH.h"

class Body : public IBody {
public:
	// コンストラクタ
	Body() : mType(ShapeType::None), mPosition(Vector3::Zero), mMatrix(Matrix::Identity), mRadius(0.0f), mLength(0.0f), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(Vector3::Zero), mEnabled(false){}
	// コンストラクタ(球)
	Body(const ShapeType& type, const Vector3& position, const float& radius) :
		mType(type), mPosition(position), mMatrix(Matrix::Identity), mRadius(radius), mLength(0.0f), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(Vector3::Zero), mEnabled(true) {}
	// コンストラクタ(線分)
	Body(const ShapeType& type, const Vector3& position, const Matrix& mat, const float& length) :
		mType(type), mPosition(position), mMatrix(mat), mRadius(0.0f), mLength(length), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(Vector3::Zero), mEnabled(true) {}
	// コンストラクタ(レイ)
	Body(const ShapeType& type, const Vector3& position, const Matrix& mat, const Vector3& direction) :
		mType(type), mPosition(position), mMatrix(Matrix::Identity), mRadius(0.0f), mLength(0.0f), mDirection(direction), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(Vector3::Zero), mEnabled(true) {}
	// コンストラクタ(カプセル)
	Body(const ShapeType& type, const Vector3& position, const Matrix& mat, const float& radius, const float& length) :
		mType(type), mPosition(position), mMatrix(mat), mRadius(radius), mLength(length), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(Vector3::Zero), mEnabled(true) {}
	// コンストラクタ(AABB)
	Body(const ShapeType& type, const Vector3& position, const Vector3 & min, const Vector3 & max) :
		mType(type), mPosition(Vector3::Zero), mMatrix(Matrix::Identity), mRadius(0.0f), mLength(0.0f), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(min), mMax(max), mExtents(Vector3::Zero), mEnabled(true) {}
	// コンストラクタ(OBB)
	Body(const ShapeType& type, const Vector3& position, const Vector3& extents) :
		mType(type), mPosition(position), mMatrix(Matrix::Identity), mRadius(0.0f), mLength(0.0f), mDirection(Vector3::Zero), mHeight(0.0f), mWidth(0.0f), mDepth(0.0f), mMin(Vector3::Zero), mMax(Vector3::Zero), mExtents(extents), mEnabled(true) {}
	// デストラクタ
	virtual ~Body(){}

	// 判定のON、OFF
	virtual void active(bool active) override { mEnabled = active; }
	// 判定があるかどうか
	virtual bool enabled() const override { return mEnabled; }

	// 形状の取得
	virtual ShapeType type() const override { return mType; }
	// 中心座標の取得
	virtual Vector3 position() const override { return mPosition; }
	// 変換行列の取得
	virtual Matrix matrix() const override { return mMatrix; }
	// 半径の取得
	virtual float radius() const override { return mRadius; }
	// 長さの取得
	virtual float length() const override { return mLength; }
	// 方向の取得
	virtual Vector3 direction() const override { return mDirection; }

	// 縦幅の取得
	virtual float height() const override { return mHeight; }
	// 横幅の取得
	virtual float width() const override { return mWidth; }
	// 奥行の取得
	virtual float depth() const override { return mDepth; }
	// 矩形の最小点の取得
	virtual Vector3 box_min() const override { return mMin; }
	// 矩形の最大点の取得
	virtual Vector3 box_max() const override { return mMax; }
	// 矩形の大きさの取得
	virtual Vector3 extents() const override { return mExtents; }
	// 矩形の軸の取得
	virtual Vector3 axis(const int index) const override { return mAxis[index]; }
	// 点の取得
	virtual Vector3 points(const int index) const override { return mPoints[index]; }
	
protected:
	// 形状
	ShapeType mType;
	// 中心座標
	Vector3 mPosition;
	// 変換行列
	Matrix mMatrix;
	// 半径
	float mRadius;
	// 長さ
	float mLength;

	// レイ用
	// 方向
	Vector3 mDirection;
	
	// ボックス用
	// 縦幅
	float mHeight;
	// 横幅
	float mWidth;
	// 奥行
	float mDepth;

	// 矩形の最小点
	Vector3 mMin;
	// 矩形の最大点
	Vector3 mMax;

	// 矩形の大きさ
	Vector3 mExtents;
	// 矩形の軸
	Vector3 mAxis[3];

	// 点
	Vector3 mPoints[4];

	// 判定があるかどうか
	bool mEnabled;
};

