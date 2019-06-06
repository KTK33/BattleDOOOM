#pragma once

#include <unordered_map>
#include <string>

class EffectAsset
{
public:
	//コンストラクタ
	EffectAsset();

	//デストラクタ
	~EffectAsset();

	//読み込み
	bool load(int id, const std::string& file_name);

	//削除
	void erase(int id);

	//消去
	void clear();

	//ハンドルの取得
	int operator[](int id)const;

	//コピー禁止
	EffectAsset(const EffectAsset&) = delete;
	EffectAsset&operator=(const EffectAsset&) = delete;

private:
	//モデルデータマップ
	std::unordered_map<int, int> asset_;
};