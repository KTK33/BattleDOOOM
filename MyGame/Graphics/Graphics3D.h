#ifndef GRAPHICS_3D_H_
#define GRAPHICS_3D_H_

#include "../Math/MathH.h"
// ライト構造体
struct Light {
    enum class Type {
        Directional,    // 平行光源
        Point,          // ポイントライト
        Spot            // スポットライト
    };
    Type    type{ Type::Directional };          // ライトのタイプ
    Vector3 direction{ 1.0f, -1.0f, 1.0f };     // ライトの方向
    Vector3 position{ 0.0f, 0.0f, 0.0f };       // ライトの座標
    Color   ambient{ 0.3f, 0.3f, 0.3f, 1.0f };  // 環境光
    Color   diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };  // 拡散反射光
    Color   specular{ 1.0f, 1.0f, 1.0f, 1.0f }; // 鏡面反射光
    float   attenuation0{ 0.1f };               // 減衰パラメータ１
    float   attenuation1{ 0.0f };               // 減衰パラメータ２
    float   attenuation2{ 0.0f };               // 減衰パラメータ３
    float   range{ 2000.0f };                   // ライトの影響範囲
    float   out_angle{ 114.0f };                // スポットライトの外側の角度
    float   in_angle{ 114.0f };                 // スポットライトの内側の角度
};

// ブレンドモード
enum class BlendMode {
    None,       // 無効
    Alpha,      // アルファブレンド
    Add,        // 加算ブレンド
    Sub         // 減算ブレンド
};

// 3Dグラフィックスクラス
class Graphics3D {
public:
    // 初期化
    static void initialize();
    // 終了
    static void finalize();

    // スクリーンの消去
    static void clear();
    // スクリーンの消去カラーの設定
    static void clear_color(float r, float g, float b);

    // ビューポートの設定
    static void viewport(int x, int y, int w, int h);
    // 視野変換行列の設定
    static void view_matrix(const Matrix& view);
    // 透視変換行列の設定
    static void projection_matrix(const Matrix& projection);
    // 透視変換行列の取得
    static Matrix view_matrix();
    // 透視変換行列の取得
    static Matrix projection_matrix();

    // ライトの設定
    static void light(const Light& light);
    // ライトの取得
    static Light light();

    // ライティングを有効にする
    static void enable_lighting();
    // ライティングを無効にする
    static void disable_lighting();
    // Zバッファを有効にする
    static void enable_z_buffer();
    // Zバッファを無効にする
    static void disable_z_buffer();
    // Zバッファに書き込みを行う
    static void enable_write_z_buffer();
    // Zバッファに書き込みを行わない
    static void disable_write_z_buffer();

    // ブレンドモードの設定
    static void blend_mode(BlendMode mode, float a = 1.0f);

private:
    // ライトの設定
    static Light    light_;
};

#endif
