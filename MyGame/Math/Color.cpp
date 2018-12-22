#include "Color.h"
#include "MathHelper.h"
#include <algorithm>

// íËêî
const Color Color::Black(0.0f, 0.0f, 0.0f, 1.0f);           // Color(0,  0,  0, 1)
const Color Color::White(1.0f, 1.0f, 1.0f, 1.0f);           // Color(1,  1,  1, 1)

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {
}

Color Color::Lerp(const Color& value1, const Color& value2, float amount) {
    return Color(
        MathHelper::Lerp(value1.r, value2.r, amount),
        MathHelper::Lerp(value1.g, value2.g, amount),
        MathHelper::Lerp(value1.b, value2.b, amount),
        MathHelper::Lerp(value1.a, value2.a, amount));
}

Color Color::Min(const Color & value1, const Color & value2) {
    return Color(
        std::min(value1.r, value2.r),
        std::min(value1.g, value2.g),
        std::min(value1.b, value2.b),
        std::min(value1.a, value2.a));
}

Color Color::Max(const Color & value1, const Color & value2) {
    return Color(
        std::max(value1.r, value2.r),
        std::max(value1.g, value2.g),
        std::max(value1.b, value2.b),
        std::max(value1.a, value2.a));
}

Color Color::Clamp(const Color & value1, const Color & min, const Color & max) {
    return Color(
        MathHelper::Clamp(value1.r, min.r, max.r),
        MathHelper::Clamp(value1.g, min.g, max.g),
        MathHelper::Clamp(value1.b, min.b, max.b),
        MathHelper::Clamp(value1.a, min.a, max.a));
}

Color& operator += (Color & c1, const Color & c2) {
    c1.r += c2.r;
    c1.g += c2.g;
    c1.b += c2.b;
    c1.a += c2.a;
    return c1;
}

Color& operator -= (Color & c1, const Color & c2) {
    c1.r -= c2.r;
    c1.g -= c2.g;
    c1.b -= c2.b;
    c1.a -= c2.a;
    return c1;
}

Color& operator *= (Color & c1, const Color & c2) {
    c1.r *= c2.r;
    c1.g *= c2.g;
    c1.b *= c2.b;
    c1.a *= c2.a;
    return c1;
}

Color& operator *= (Color & c, float s) {
    c.r *= s;
    c.g *= s;
    c.b *= s;
    c.a *= s;
    return c;
}

Color& operator /= (Color & c, float s) {
    c.r /= s;
    c.g /= s;
    c.b /= s;
    c.a /= s;
    return c;
}

Color operator + (Color c1, const Color & c2) {
    return c1 += c2;
}

Color operator - (Color c1, const Color & c2) {
    return c1 -= c2;
}

Color operator * (Color c1, const Color & c2) {
    return c1 *= c2;
}

Color operator * (Color c, float s) {
    return c *= s;
}

Color operator * (float s, Color c) {
    return c *= s;
}

Color operator / (Color c, float s) {
    return c /= s;
}
