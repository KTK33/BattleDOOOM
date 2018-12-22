#include "MathHelper.h"
#include <cmath>
#include <algorithm>

// 整数を渡し、絶対値を返す
int MathHelper::Abs(int value)
{
	return (int)fabsf((float)value);
}

// πの値を表します。
const float MathHelper::Pi = 3.14159265359f;

float MathHelper::Clamp(float value, float min, float max) {
    return std::max(min, std::min(value, max));
}

float MathHelper::Distance(float n1, float n2) {
    return std::abs(n1 - n2);
}

float MathHelper::Lerp(float value1, float value2, float amount) {
    return (value1 * (1.0f - amount)) + (value2 * amount);
}

float MathHelper::ToDegrees(float radians) {
    return radians * (180.f / MathHelper::Pi);
}

float MathHelper::ToRadians(float degree) {
    return degree *  (MathHelper::Pi / 180.0f);
}

float MathHelper::Sin(float degree) {
    return std::sin(ToRadians(degree));
}

float MathHelper::Cos(float degree) {
    return std::cos(ToRadians(degree));
}

float MathHelper::Tan(float degree) {
    return std::tan(ToRadians(degree));
}

float MathHelper::ASin(float s) {
    return ToDegrees(std::asin(s));
}

float MathHelper::ACos(float c) {
    return ToDegrees(std::acos(c));
}

float MathHelper::ATan(float y, float x) {
    return ToDegrees(std::atan2(y, x));
}
