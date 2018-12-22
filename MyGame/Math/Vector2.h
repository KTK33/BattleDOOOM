#ifndef VECTOR2_H_
#define VECTOR2_H_

// 2D�x�N�g��
struct Vector2 {
    float x{ 0.0f };  // x����
    float y{ 0.0f };  // y����

    // �R���X�g���N�^
    Vector2() = default;
    // �R���X�g���N�^
    Vector2(float x, float y);

    // ���ς����߂�
    float dot(const Vector2& other) const;
    // �O�ς����߂�
    float cross(const Vector2& other) const;
    // ���������߂�
    float length() const;
    // ���K�������x�N�g�������߂�
    Vector2 normalize() const;

    // �p�x����x�N�g�����쐬
    static Vector2 from_angle(float degree);
    // �x�N�g���������Ă���p�x�����߂�
    float to_angle() const;
    // ��]
    Vector2 rotate(float degree) const;
    // �Q�̃x�N�g���Ȃ��p�x�����߂�
    float inner_angle(const Vector2& other) const;

    // ���������߂�
    float distance(const Vector2& other) const;
    // ���`���
    Vector2 lerp(const Vector2& end, float t) const;
    // �N�����v
    Vector2 clamp(const Vector2& min, const Vector2& max) const;
    // �^�[�Q�b�g�����̃x�N�g�������߂�
    Vector2 to_target(const Vector2& target) const;
    // �^�[�Q�b�g�����̊p�x�����߂�
    float to_target_angle(const Vector2& target) const;

    // �[���x�N�g�����H
    bool is_zero() const;

    // �萔
    static const Vector2 Zero;  //  0.0f  0.0f
    static const Vector2 One;   //  1.0f  1.0f
    static const Vector2 Left;  // -1.0f  0.0f
    static const Vector2 Right; //  1.0f  0.0f
    static const Vector2 Down;  //  0.0f  1.0f
    static const Vector2 Up;    //  0.0f -1.0f
};

// ���Z�q�I�[�o�[���[�h
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

