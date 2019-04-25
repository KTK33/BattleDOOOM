#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <DxLib.h>

struct Matrix;
struct Quaternion;

// 3Dベクトル
struct Vector3 {
    float   x;  // x成分
    float   y;  // y成分
    float   z;  // z成分

    // コンストラクタ
    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    // ベクトルの長さを計算します
    float Length() const;
    // ベクトルの長さの平方を計算します
    float LengthSquared() const;
    // 単位ベクトルを作成します
    Vector3& Normalize();

    // 指定ベクトルから単位ベクトルを作成します
    static Vector3 Normalize(const Vector3& value);
    // 2つのベクトルの内積を計算します
    static float Dot(const Vector3& vector1, const Vector3& vector2);
    // 2つのベクトルの外積を計算します
    static Vector3 Cross(const Vector3& vector1, const Vector3& vector2);
    // 2つのベクトル間の距離を計算します
    static float Distance(const Vector3& vector1, const Vector3& vector2);
    // 2 つの直交ベクトル間の距離を計算します。 
    static float DistanceSquared(const Vector3& vector1, const Vector3& vector2);
    // 2 つのベクトル間の線形補間を行います
    static Vector3 Lerp(const Vector3& value1, const Vector3& value2, float amount);
    // 一致する各成分ペアの最も低い値を含むベクトルを返します
    static Vector3 Min(const Vector3& vector1, const Vector3& vector2);
    // 一致する各成分ペアの最も高い値を含むベクトルを返します
    static Vector3 Max(const Vector3& vector1, const Vector3& vector2);
    //  値を指定された範囲内に制限します
    static Vector3 Clamp(const Vector3& value1, const Vector3& min, const Vector3& max);
    // 指定された Matrix によって、Vector3をトランスフォームします
    static Vector3 Transform(const Vector3& position, const Matrix& matrix);
    // 指定された Matrix によって、法線ベクトルをトランスフォームします
    static Vector3 TransformNormal(const Vector3& position, const Matrix& matrix);

    // ヨー・ピッチからベクトルを作成
    static Vector3 CreateFromYawPitch(float yaw, float pitch);
    // ピッチを取得
    float Pitch() const;
    // ヨーを取得
    float Yaw() const;
    //  2 つのベクトル間の鋭角を返します
    static float Angle(const Vector3& from, const Vector3& to);
	//Dxlib用変換関数
	static VECTOR Vector3ToVECTOR(const Vector3& v);
	//Dxlib用変換関数
	static Vector3 VECTORToVector3(const VECTOR& v);


    // 定数
    static const Vector3 Up;            // Vector3( 0,  1,  0)
    static const Vector3 Down;          // Vector3( 0, -1,  0)
    static const Vector3 Left;          // Vector3(-1,  0,  0)
    static const Vector3 Right;         // Vector3( 1,  0,  0)
    static const Vector3 Backward;      // Vector3( 0,  0, -1)
    static const Vector3 Forward;       // Vector3( 0,  0,  1)
    static const Vector3 UnitX;         // Vector3( 1,  0,  0)
    static const Vector3 UnitY;         // Vector3( 0,  1,  0)
    static const Vector3 UnitZ;         // Vector3( 0,  1,  1)
    static const Vector3 One;           // Vector3( 1,  1,  1)
    static const Vector3 Zero;          // Vector3( 0,  0,  0)

#ifdef  __DXLIB
    // Dxlib用変換関数
    Vector3(const DxLib::VECTOR& v) : x(v.x), y(v.y), z(v.z) {}
    // DxLibのベクトルに変換
    operator DxLib::VECTOR() const {
        return { x, y, z };
    }
#endif
};

// 単項演算子オーバーロード
Vector3 operator - (const Vector3& v);

// 代入演算子オーバーロード
Vector3& operator += (Vector3& v1, const Vector3& v2);
Vector3& operator -= (Vector3& v1, const Vector3& v2);
Vector3& operator *= (Vector3& v, float s);
Vector3& operator /= (Vector3& v, float s);

// ２項演算子オーバーロード
Vector3 operator + (Vector3 v1, const Vector3& v2);
Vector3 operator - (Vector3 v1, const Vector3& v2);
Vector3 operator * (Vector3 v, float s);
Vector3 operator * (float s, Vector3 v);
Vector3 operator / (Vector3 v, float s);

#endif

// end of file
