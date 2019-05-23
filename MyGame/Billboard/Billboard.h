#ifndef BILLBOARD_H_
#define BILLBOARD_H_

#include "../Texture/TextureAsset.h"
#include "../Math/MathH.h"
#include <string>

// ビルボードクラス
class Billboard {
public:
    // 初期化
    static void initialize();
    // 終了処理
    static void finalize();
    // 読み込み
    static bool load(int id, const std::string& file_name);
    // 削除
    static void erase(int id);
    // バインド
    static void bind(int id);
    // 描画
    static void draw(const Vector3& position, float size, float cx = 0.5f, float cy = 0.5f, float angle = 0.0f);
	//変形描画(左上、右上、右下、左下の頂点の座標)
	static void Mobidraw(const Vector3& position, Vector2 pos1, Vector2 pos2,Vector2 pos3, Vector2 pos4);

private:
    // バインド中のイメージ
    static int          image_;
    // イメージアセット
    static TextureAsset asset_;
};

#endif