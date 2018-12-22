#include "Vector2.h"
#include "MathHelper.h"
#include <cmath>
#include <cfloat>
#include <algorithm>

// �萔�̎���
const Vector2 Vector2::Zero{ 0.0f, 0.0f };
const Vector2 Vector2::One{ 1.0f, 1.0f };
const Vector2 Vector2::Left{ -1.0f, 0.0f };
const Vector2 Vector2::Right{ 1.0f, 0.0f };
const Vector2 Vector2::Up{ 0.0f, -1.0f };
const Vector2 Vector2::Down{ 0.0f, 1.0f };

// �R���X�g���N�^
Vector2::Vector2(float x, float y) : x{ x }, y{ y } {
}

// ���ς����߂�
float Vector2::dot(const Vector2 & other) const {
    return (x * other.x) + (y * other.y);
}

// �O�ς����߂�
float Vector2::cross(const Vector2 & other) const {
    return (x * other.y) - (y * other.x);
}

// ���������߂�
float Vector2::length() const {
    return std::sqrt(dot(*this));
}

// ���������߂�
float Vector2::distance(const Vector2 & other) const {
    return (*this - other).length();
}

// ���K������
Vector2 Vector2::normalize() const {
    const auto len = length();
    if (len < FLT_EPSILON) return Vector2::Zero;
    return *this / len;
}

// �[���x�N�g�����H
bool Vector2::is_zero() const {
    return (x == 0.0f) && (y == 0.0f);
}

// �x�N�g���������Ă���p�x�����߂�
float Vector2::to_angle() const {
    if (is_zero()) return 0.0f; // �[���x�N�g���͊p�x�����߂��Ȃ�
    return MathHelper::ToDegrees(std::atan2(y, x)); // �x���@�ɕϊ�
}

// �^�[�Q�b�g�����̃x�N�g�������߂�
Vector2 Vector2::to_target(const Vector2& target) const {
    return (target - *this).normalize();
}

// �^�[�Q�b�g�����̊p�x�����߂�
float Vector2::to_target_angle(const Vector2& target) const {
    return to_target(target).to_angle();
}

// �p�x����x�N�g�����쐬
Vector2 Vector2::from_angle(float degree) {
    const auto rad = MathHelper::ToRadians(degree); // �ʓx�@�ɕϊ�
    return { std::cos(rad), std::sin(rad) };
}

// �Q�̃x�N�g���Ȃ��p�x�����߂�
float Vector2::inner_angle(const Vector2& other) const {
    const auto& n1 = normalize();
    const auto& n2 = other.normalize();
    const auto cos = n1.dot(n2);
    return MathHelper::ToDegrees(std::acos(cos));
}

// ���`���
Vector2 Vector2::lerp(const Vector2& end, float t) const {
    return { MathHelper::Lerp(x, end.x, t), MathHelper::Lerp(y, end.y, t) };
}

// �N�����v
Vector2 Vector2::clamp(const Vector2& min, const Vector2& max) const {
    return { MathHelper::Clamp(x, min.x, max.x), MathHelper::Clamp(y, min.y, max.y) };
}

// ��]
Vector2 Vector2::rotate(float degree) const {
    const auto rad = MathHelper::ToRadians(degree); // �ʓx�@�ɕϊ�
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
