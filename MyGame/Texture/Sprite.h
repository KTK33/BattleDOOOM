#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "SpriteID.h"
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"

class Sprite
{
private:
	Sprite() = default;
	~Sprite();
public:
	static Sprite &GetInstance() {
		static Sprite s;
		return s;
	}

	///<summary>
	/// 初期化処理
	///</summary>
	void Initialize();

	/// 通常画像の読み込み(アセット名、IDの指定)
	void Load(const std::string& filename, const SPRITE_ID& id);

	/**
		@param lineSize 横の分割数
		@param divCount 分割読み込み数
	*/
	void DivLoad(const std::string& filename, const SPRITE_ID& id, int spriteWidth, int spriteHeight, int divXSize, int divYSize, int divCount);

	/// 読み込んだ画像をすべて削除する
	void DeleteAll();
	///選んだ画像を削除する
	void DeleteNum(const SPRITE_ID& id);
	void DrawSetCenter(const SPRITE_ID& id, const Vector2& position);
	/// 通常画像の描画
	void Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f);
	void DrawBillBoard(const SPRITE_ID& id, const Vector3& position, const Vector2& origin = Vector2::Zero, float size = 1.0f, float angle = 0.0f);
	void Draw3D(SPRITE_ID id, const Vector2& position, const Vector2& size, int r = 255, int g = 255, int b = 255, int a = 255, float startangle = 0.0f, float Xangle = 0.0f, float Zangle = 0.0f, float Zoffset = 0.0f);
	/**
		@param divNum 分割画像インデックス
	*/
	void DrawDivSprite(const SPRITE_ID& id, const Vector2& position, int divNum, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f);
	/// 画像のサイズを取得する
	Vector2 GetSize(const SPRITE_ID& id) const;
	//画像のサイズを取得する
	Vector2 GetSizeDiv(const SPRITE_ID& id) const;
	//ハンドルを取得する
	int GetHandle(const SPRITE_ID& id) const;
	//画像の指定した一部のみ描画
	void DrawPart(const SPRITE_ID& id, const Vector2& position, int x, int y, int w, int h);
	void DrawPartExtend(const SPRITE_ID& id, const Vector2& position,const Vector2& exposition, int x, int y, int w, int h);
	void DrawPartRota(const SPRITE_ID& id, const Vector2& position,int x, int y, int w, int h,const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f);


private:
	// 通常画像
	std::unordered_map<SPRITE_ID, int> m_sprites;

	std::unordered_map<SPRITE_ID, std::vector<int>> m_divSprites;

};