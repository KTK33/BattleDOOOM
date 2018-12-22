#ifndef VECTOR2_H_
#define VECTOR2_H_

// 2Dベクトル
struct Vector2 {
    float x{ 0.0f };  // x成分
    float y{ 0.0f };  // y成分

    // コンストラクタ
    Vector2() = default;
    // コンストラクタ
    Vector2(float x, float y);

    // 内積を求める
    float dot(const Vector2& other) const;
    // 外積を求める
    float cross(const Vector2& other) const;
    // 長さを求める
    float length() const;
    // 正規化したベクトルを求める
    Vector2 normalize() const;

    // 角度からベクトルを作成
    static Vector2 from_angle(float degree);
    // ベクトルが向いている角度を求める
    float to_angle() const;
    // 回転
    Vector2 rotate(float degree) const;
    // ２つのベクトルなす角度を求める
    float inner_angle(const Vector2& other) const;

    // 距離を求める
    float distance(const Vector2& other) const;
    // 線形補間
    Vector2 lerp(const Vector2& end, float t) const;
    // クランプ
    Vector2 clamp(const Vector2& min, const Vector2& max) const;
    // ターゲット方向のベクトルを求める
    Vector2 to_target(const Vector2& target) const;
    // ターゲット方向の角度を求める
    float to_target_angle(const Vector2& target) const;

    // ゼロベクトルか？
    bool is_zero() const;

    // 定数
    static const Vector2 Zero;  //  0.0f  0.0f
    static const Vector2 One;   //  1.0f  1.0f
    static const Vector2 Left;  // -1.0f  0.0f
    static const Vector2 Right; //  1.0f  0.0f
    static const Vector2 Down;  //  0.0f  1.0f
    static const Vector2 Up;    //  0.0f -1.0f
};

// 演算子オーバーロード
Vector2& operator += (Vector2& lhs, const Vector2& rhs);
Vector2& operator -= (Vector2& lhs, const Vector2& rhs);
Vector2& operator *= (Vector2& lhs, float scalar);
Vector2& operator /= (Vector2& lhs, float scalar);
const Vector2 operator + (const Vector2& lhs, const Vector2& rhs);
const Vector2 operator - (const Vector2& lhs, const Vector2& rhs);
const Vector2 operator * (const Vector2& lhs, float scalar);
const Vector2 operator * (float scalar, const Vector2& rhs);
const Vector2 operator / (const Vector2& lhs, float scalar);
const Vector2 operator - (const Vector2& v);
bool operator == (const Vector2& lhs, const Vector2& rhs);
bool operator != (const Vector2& lhs, const Vector2& rhs);
bool operator < (const Vector2& lhs, const Vector2& rhs);

#endif // !VECTOR2_H_

