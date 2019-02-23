#pragma once

// マスヘルパークラス
class MathHelper
{
public:
	// πの値を表します。
	static const float Pi;

	// 整数を渡し、絶対値を返す
	static int Abs(int value);
	// 実数を渡し、絶対値を返す
	static float Abs(float value);
	// ２つの整数値の差の絶対値を計算します
	static int Distance(int n1, int n2);
	// ２つの実数値の差の絶対値を計算します
	static float Distance(float n1, float n2);
	// ２つの整数を渡し、小さいほうを返す
	static int Min(int value1, int value2);
	// ２つの実数を渡し、小さいほうを返す
	static float Min(float value1, float value2);
	// ２つの整数を渡し、大きいほうを返す
	static int Max(int value1, int value2);
	// ２つの実数を渡し、大きいほうを返す
	static float Max(float value1, float value2);
	// 整数の符号を求める
	static int Sign(int value);
	// 実数の符号を求める
	static int Sign(float value);
	// 整数の平方根を返す
	static float Sqrt(int value);
	// 実数の平方根を返す
	static float Sqrt(float value);
	static int gcd(int a, int b)
	{
		int c;

		if (a < b) {
			a += b; b = a - b; a -= b;
		}

		while (b != 0) {
			c = a % b;
			a = b;
			b = c;
		}

		return a;
	}
	// 整数値を指定された範囲内に制限します
	static int Clamp(int value, int min, int max);
	// 実数値を指定された範囲内に制限します
	static float Clamp(float value, float min, float max);
	// 2つの値の間を線形補間します
	static float Lerp(float value1, float value2, float amount);
	//2つの値を基準にして、0.0～1.0の間をS字カーブ型に補間します
	static float Smoothstep(float edge0, float edge1, float x);
	// ラジアンを度に変換します。
	static float ToDegrees(float radians);
	// 度をラジアンに変換します。
	static float ToRadians(float degree);
	// サイン（０～３６０）
	static float Sin(float degree);
	// コサイン（０～３６０）
	static float Cos(float degree);
	// タンジェント（０～３６０）
	static float Tan(float degree);
	// 逆サイン
	static float ASin(float s);
	// 逆コサイン
	static float ACos(float c);
	// 逆タンジェント
	static float ATan(float y, float x);

	// 整数値同士の余りを算出
	static int Mod(int value1, int value2);
	// 実数値同士の余りを算出
	static float Mod(float value1, float value2);

	// 整数のべき乗を返す (xのy乗)
	static int Pow(int x, int y);
	// 実数のべき乗を返す (xのy乗)
	static float Pow(float x, float y);
};