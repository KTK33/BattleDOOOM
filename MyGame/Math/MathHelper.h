#ifndef MATH_HELPER_H_
#define MATH_HELPER_H_

// マスヘルパークラス
class MathHelper {
public:
	// 整数を渡し、絶対値を返す
	static int Abs(int value);
    // πの値を表します。
    static const float Pi;
    // 値を指定された範囲内に制限します
    static float Clamp(float value, float min, float max);
    // 2つの値の差の絶対値を計算します
    static float Distance(float n1, float n2);
    // 2つの値の間を線形補間します
    static float Lerp(float value1, float value2, float amount);
    // ラジアンを度に変換します。
    static float ToDegrees(float radians);
    // 度をラジアンに変換します。
    static float ToRadians(float degree);
    // サイン
    static float Sin(float degree);
    // コサイン
    static float Cos(float degree);
    // タンジェント
    static float Tan(float degree);
    // 逆サイン
    static float ASin(float s);
    // 逆コサイン
    static float ACos(float c);
    // 逆タンジェント
    static float ATan(float y, float x);
};

#endif
