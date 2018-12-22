#include "Vector2.h"
#include "MathHelper.h"
#include <cmath>
#include <cfloat>
#include <algorithm>

// 定数の実体
const Vector2 Vector2::Zero{ 0.0f, 0.0f };
const Vector2 Vector2::One{ 1.0f, 1.0f };
const Vector2 Vector2::Left{ -1.0f, 0.0f };
const Vector2 Vector2::Right{ 1.0f, 0.0f };
const Vector2 Vector2::Up{ 0.0f, -1.0f };
const Vector2 Vector2::Down{ 0.0f, 1.0f };

// コンストラクタ
Vector2::Vector2(float x, float y) : x{ x }, y{ y } {
}

// 内積を求める
float Vector2::dot(const Vector2 & other) const {
    return (x * other.x) + (y * other.y);
}

// 外積を求める
float Vector2::cross(const Vector2 & other) const {
    return (x * other.y) - (y * other.x);
}

// 長さを求める
float Vector2::length() const {
    return std::sqrt(dot(*this));
}

// 距離を求める
float Vector2::distance(const Vector2 & other) const {
    return (*this - other).length();
}

// 正規化する
Vector2 Vector2::normalize() const {
    const auto len = length();
    if (len < FLT_EPSILON) return Vector2::Zero;
    return *this / len;
}

// ゼロベクトルか？
bool Vector2::is_zero() const {
    return (x == 0.0f) && (y == 0.0f);
}

// ベクトルが向いている角度を求める
float Vector2::to_angle() const {
    if (is_zero()) return 0.0f; // ゼロベクトルは角度を求められない
    return MathHelper::ToDegrees(std::atan2(y, x)); // 度数法に変換
}

// ターゲット方向のベクトルを求める
Vector2 Vector2::to_target(const Vector2& target) const {
    return (target - *this).normalize();
}

// ターゲット方向の角度を求める
float Vector2::to_target_angle(const Vector2& target) const {
    return to_target(target).to_angle();
}

// 角度からベクトルを作成
Vector2 Vector2::from_angle(float degree) {
    const auto rad = MathHelper::ToRadians(degree); // 弧度法に変換
    return { std::cos(rad), std::sin(rad) };
}

// ２つのベクトルなす角度を求める
float Vector2::inner_angle(const Vector2& other) const {
    const auto& n1 = normalize();
    const auto& n2 = other.normalize();
    const auto cos = n1.dot(n2);
    return MathHelper::ToDegrees(std::acos(cos));
}

// 線形補間
Vector2 Vector2::lerp(const Vector2& end, float t) const {
    return { MathHelper::Lerp(x, end.x, t), MathHelper::Lerp(y, end.y, t) };
}

// クランプ
Vector2 Vector2::clamp(const Vector2& min, const Vector2& max) const {
    return { MathHelper::Clamp(x, min.x, max.x), MathHelper::Clamp(y, min.y, max.y) };
}

// 回転
Vector2 Vector2::rotate(float degree) const {
    const auto rad = MathHelper::ToRadians(degree); // 弧度法に変換
    return { x * std::cos(rad) - y * std::sin(rad), x * std::sin(rad) + y * std::cos(rad) };
}

Vector2& operator += (Vector2& lhs, const Vector2& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

Vector2& operator -= (Vector2& lhs, const Vector2& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

Vector2& operator *= (Vector2& lhs, float scalar) {
    lhs.x *= scalar;
    lhs.y *= scalar;
    return lhs;
}

Vector2& operator /= (Vector2& lhs, float scalar) {
    lhs.x /= scalar;
    lhs.y /= scalar;
    return lhs;
}

const Vector2 operator + (const Vector2& lhs, const Vector2& rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

const Vector2 operator - (const Vector2& lhs, const Vector2& rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

const Vector2 operator * (const Vector2& lhs, float scalar) {
    return { lhs.x * scalar, lhs.y * scalar };
}

const Vector2 operator * (float scalar, const Vector2& rhs) {
    return { rhs.x * scalar, rhs.y * scalar };
}

const Vector2 operator / (const Vector2& lhs, float scalar) {
    return { lhs.x / scalar, lhs.y / scalar };
}

const Vector2 operator - (const Vector2& v) {
    return { -v.x, -v.y };
}

bool operator == (const Vector2& lhs, const Vector2& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == lhs.y);
}

bool operator != (const Vector2& lhs, const Vector2& rhs) {
    return !(lhs == rhs);
}

bool operator < (const Vector2& lhs, const Vector2& rhs) {
    if (lhs.x != rhs.x) return lhs.x < rhs.x;
    if (lhs.y != rhs.y) return lhs.y < rhs.y;
    return true;
}

// end of files
