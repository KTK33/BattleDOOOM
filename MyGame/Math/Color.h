#ifndef COLOR_H_
#define COLOR_H_

// カラー
struct Color {
    float   r;  // 赤
    float   g;  // 緑
    float   b;  // 青
    float   a;  // アルファ

    // コンストラクタ
    Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
    // 2つのカラー間の線形補間を行います
    static Color Lerp(const Color& value1, const Color& value2, float amount);
    // 一致する各成分ペアの最も低い値を含むカラーを返します
    static Color Min(const Color& value1, const Color& value2);
    // 一致する各成分ペアの最も高い値を含むカラーを返します
    static Color Max(const Color& value1, const Color& value2);
    //  値を指定された範囲内に制限します
    static Color Clamp(const Color& value1, const Color& min = Color(0.0f, 0.0f, 0.0f, 0.0f), const Color& max = Color(1.0f, 1.0f, 1.0f, 1.0f));

    // 定数
    static const Color Black;           // Color(0, 0, 0, 1)
    static const Color White;           // Color(1, 1, 1, 1)
};

// 代入演算子オーバーロード
Color& operator += (Color& c1, const Color& c2);
Color& operator -= (Color& c1, const Color& c2);
Color& operator *= (Color& c1, const Color& c2);
Color& operator *= (Color& c, float s);
Color& operator /= (Color& c, float s);

// ２項演算子オーバーロード
Color operator + (Color c1, const Color& c2);
Color operator - (Color c1, const Color& c2);
Color operator * (Color c1, const Color& c2);
Color operator * (Color c, float s);
Color operator * (float s, Color c);
Color operator / (Color c, float s);

#endif

// end of file
