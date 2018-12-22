#ifndef QUATERNION_H_
#define QUATERNION_H_

struct Vector3;
struct Matrix;

// クォータニオン
struct Quaternion {
    float x;        // x成分
    float y;        // y成分
    float z;        // z成分
    float w;        // w成分

    // コンストラクタ
    Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
    // コンストラクタ
    Quaternion(const Vector3& axis, float angle);

    // 正規化する
    static Quaternion Normalize(const Quaternion& q);
    // 正規化する
    Quaternion& Normalize();

    // 内積を求める
    static float Dot(const Quaternion& q1, const Quaternion& q2);
    // ノルムを求める
    float Length() const;

    // 球面線形補間
    static Quaternion Slerp(const Quaternion& value1, const Quaternion& value2, float amount);

    // 回転行列からクオータニオンを作成
    static Quaternion CreateFromRotationMatrix(const Matrix& matrix);

    // 単位クオータニオン
    static const Quaternion Identity;
};

// 単項演算子オーバーロード
Quaternion operator - (const Quaternion& q);

// 代入演算子オーバーロード
Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);

// ２項演算子オーバーロード
Quaternion operator + (Quaternion q1, const Quaternion& q2);
Quaternion operator - (Quaternion q1, const Quaternion& q2);
Quaternion operator * (Quaternion q1, const Quaternion& q2);
Quaternion operator * (Quaternion q, float s);
Quaternion operator * (float s, Quaternion q);
Quaternion operator / (Quaternion q, float s);

#endif

// end of file
