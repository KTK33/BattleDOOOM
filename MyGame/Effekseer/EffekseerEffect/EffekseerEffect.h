#ifndef _EFFEKSEER_EFFECT_H_
#define _EFFEKSEER_EFFECT_H_

#include "../EffectAsset/EffectAsset.h"
#include "../Math/Vector3.h"

class EffekseerEffect
{
public:
	//初期化
	static void initialize();

	//終了処理
	static void finalize();

	//読み込み
	static bool load(int id, const std::string& file_name);

	//削除
	static void erase(int id);

	//バインド
	static void bind(int id);

	static int play();

	//描画
	static void draw();

private:
	static int m_effect;
	static EffectAsset asset_;
};

#endif