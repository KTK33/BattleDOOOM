#include "MathHelper.h"
#include <cmath>
#include <algorithm>

// πの値を表します。
const float MathHelper::Pi = 3.14159265359f;

// 整数を渡し、絶対値を返す
int MathHelper::Abs(int value)
{
	return (int)fabsf((float)value);
}

// 実数を渡し、絶対値を返す
float MathHelper::Abs(float value)
{
	return fabsf(value);
}

// 2つの整数値の差の絶対値を計算します
int MathHelper::Distance(int n1, int n2)
{
	return MathHelper::Abs(n1 - n2);
}

// 2つの実数値の差の絶対値を計算します
float MathHelper::Distance(float n1, float n2)
{
	return MathHelper::Abs(n1 - n2);
}

// ２つの整数を渡し、小さいほうを返す
int MathHelper::Min(int value1, int value2)
{
	return std::min(value1, value2);
}

// ２つの実数を渡し、小さいほうを返す
float MathHelper::Min(float value1, float value2)
{
	return std::min(value1, value2);
}

// ２つの整数を渡し、大きいほうを返す
int MathHelper::Max(int value1, int value2)
{
	return std::max(value1, value2);
}

// ２つの実数を渡し、大きいほうを返す
float MathHelper::Max(float value1, float value2)
{
	return std::max(value1, value2);
}

// 整数の符号を求める
int MathHelper::Sign(int value)
{
	return (value > 0) - (value < 0);
}

// 実数の符号を求める
int MathHelper::Sign(float value)
{
	return static_cast<int>((value > 0) - (value < 0));
}

// 整数の平方根を返す
float MathHelper::Sqrt(int value)
{
	return sqrtf(static_cast<float>(value));
}

// 実数の平方根を返す
float MathHelper::Sqrt(float value)
{
	return sqrtf(value);
}

// 整数値を指定された範囲内に制限します
int MathHelper::Clamp(int value, int min, int max)
{
	return MathHelper::Max(min, MathHelper::Min(value, max));
}

// 実数値を指定された範囲内に制限します
float MathHelper::Clamp(float value, float min, float max)
{
	return MathHelper::Max(min, MathHelper::Min(value, max));
}

// 2つの値の間を線形補間します
float MathHelper::Lerp(float value1, float value2, float amount)
{

	return (value1 * (1.0f - amount)) + (value2 * amount);
}

float MathHelper::Smoothstep(float edge0, float edge1, float x)
{
	float t = MathHelper::Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
	return t * t * (3 - 2 * t);
}

// ラジアンを度に変換します。
float MathHelper::ToDegrees(float radians)
{
	return radians * (180.f / MathHelper::Pi);
}

// 度をラジアンに変換します。
float MathHelper::ToRadians(float degree)
{
	return degree * (MathHelper::Pi / 180.0f);
}

// サイン（０～３６０）
float MathHelper::Sin(float degree)
{
	return std::sin(ToRadians(degree));
}

// コサイン（０～３６０）
float MathHelper::Cos(float degree)
{
	return std::cos(ToRadians(degree));
}

// タンジェント（０～３６０）
float MathHelper::Tan(float degree)
{
	return std::tan(ToRadians(degree));
}

// 逆サイン
float MathHelper::ASin(float s)
{
	return ToDegrees(std::asin(s));
}

// 逆コサイン
float MathHelper::ACos(float c)
{
	return ToDegrees(std::acos(c));
}

// 逆タンジェント
float MathHelper::ATan(float y, float x)
{
	return ToDegrees(std::atan2(y, x));
}

// 整数値同士の余りを算出
int MathHelper::Mod(int value1, int value2)
{
	return (int)fmodf((float)value1, (float)value2);
}

// 実数値同士の余りを算出
float MathHelper::Mod(float value1, float value2)
{
	return fmodf(value1, value2);
}

// 整数のべき乗を返す (xのy乗)
int MathHelper::Pow(int x, int y)
{
	return static_cast<int>((int)powf((float)x, (float)y));
}

// 実数のべき乗を返す (xのy乗)
float MathHelper::Pow(float x, float y)
{
	return powf(x, y);
}

