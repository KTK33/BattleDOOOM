#pragma once

#include "DxLib.h"

// 2Dベクトル
struct Vector2 {
	float	x;	// x成分
	float	y;	// y成分

	// コンストラクタ
	Vector2(float x = 0.0f, float y = 0.0f);
	// ベクトルの長さを計算します
	float Length() const;
	// ベクトルの長さの平方を計算します
	float LengthSquared() const;
	// 単位ベクトルを作成します
	Vector2& Normalize();
	//水平方向のベクトル
	Vector2 Horizontal();
	//垂直方向のベクトル
	Vector2 Vertical();

	//2ベクトルからなす角を計算します
	static float Angle(const Vector2& vector1, const Vector2& vector2);
	// 指定ベクトルから単位ベクトルを作成します
	static Vector2 Normalize(const Vector2& value);
	// 2つのベクトルの内積を計算します
	static float Dot(const Vector2& vector1, const Vector2& vector2);
	// 2つのベクトルの外積を計算します
	static float Cross(const Vector2& vector1, const Vector2& vector2);
	// 2つのベクトル間の距離を計算します
	static float Distance(const Vector2& vector1, const Vector2& vector2);
	// 2 つの直交ベクトル間の距離を計算します。
	static float DistanceSquared(const Vector2 & vector1, const Vector2 & vector2);
	// 2 つのベクトル間の線形補間を行います
	static Vector2 Lerp(const Vector2& value1, const Vector2& value2, float amount);
	// 一致する各成分ペアの最も低い値を含むベクトルを返します
	static Vector2 Min(const Vector2& vector1, const Vector2& vector2);
	// 一致する各成分ペアの最も高い値を含むベクトルを返します
	static Vector2 Max(const Vector2& vector1, const Vector2& vector2);
	//	値を指定された範囲内に制限します
	static Vector2 Clamp(const Vector2& value1, const Vector2& min, const Vector2& max);

	//向きと基準位置、ターゲット位置を利用して、直線とポイントとの距離を計算する
	static float Point_Distance(const Vector2& direction, const Vector2& basePoint, const Vector2& targetPoint);

	//Dxlib用変換関数
	static VECTOR Vector2ToVECTOR(const Vector2& v);
	//Dxlib用変換関数
	static Vector2 VECTORToVector2(const VECTOR& v);

	// 定数
	static const Vector2 Up;			// Vector2( 0,  1)
	static const Vector2 Down;			// Vector2( 0, -1)
	static const Vector2 Left;			// Vector2(-1,  0)
	static const Vector2 Right;			// Vector2( 1,  0)
	static const Vector2 UnitX;			// Vector2( 1,  0)
	static const Vector2 UnitY;			// Vector2( 0,  1)
	static const Vector2 One;			// Vector2( 1,  1)
	static const Vector2 Zero;			// Vector2( 0,  0)
};

// 単項演算子オーバーロード
Vector2 operator - (const Vector2& v);

// 代入演算子オーバーロード
Vector2& operator += (Vector2& v1, const Vector2& v2);
Vector2& operator -= (Vector2& v1, const Vector2& v2);
Vector2& operator *= (Vector2& v, float s);
Vector2& operator /= (Vector2& v, float s);

// ２項演算子オーバーロード
Vector2 operator + (Vector2 v1, const Vector2& v2);
Vector2 operator - (Vector2 v1, const Vector2& v2);
Vector2 operator * (Vector2 v, float s);
Vector2 operator * (float s, Vector2 v);
Vector2 operator / (Vector2 v, float s);
