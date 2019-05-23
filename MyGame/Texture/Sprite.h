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
	/// ����������
	///</summary>
	void Initialize();

	/// �ʏ�摜�̓ǂݍ���(�A�Z�b�g���AID�̎w��)
	void Load(const std::string& filename, const SPRITE_ID& id);

	/**
		@param lineSize ���̕�����
		@param divCount �����ǂݍ��ݐ�
	*/
	void DivLoad(const std::string& filename, const SPRITE_ID& id, int spriteWidth, int spriteHeight, int divXSize, int divYSize, int divCount);

	/// �ǂݍ��񂾉摜�����ׂč폜����
	void DeleteAll();
	///�I�񂾉摜���폜����
	void DeleteNum(const SPRITE_ID& id);
	void DrawSetCenter(const SPRITE_ID& id, const Vector2& position);
	/// �ʏ�摜�̕`��
	void Draw(const SPRITE_ID& id, const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f);
	void DrawBillBoard(const SPRITE_ID& id, const Vector3& position, const Vector2& origin = Vector2::Zero, float size = 1.0f, float angle = 0.0f);
	void Draw3D(SPRITE_ID id, const Vector2& position, const Vector2& size, int r = 255, int g = 255, int b = 255, int a = 255, float startangle = 0.0f, float Xangle = 0.0f, float Zangle = 0.0f, float Zoffset = 0.0f);
	/**
		@param divNum �����摜�C���f�b�N�X
	*/
	void DrawDivSprite(const SPRITE_ID& id, const Vector2& position, int divNum, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f);
	/// �摜�̃T�C�Y���擾����
	Vector2 GetSize(const SPRITE_ID& id) const;
	//�摜�̃T�C�Y���擾����
	Vector2 GetSizeDiv(const SPRITE_ID& id) const;
	//�n���h�����擾����
	int GetHandle(const SPRITE_ID& id) const;
	//�摜�̎w�肵���ꕔ�̂ݕ`��
	void DrawPart(const SPRITE_ID& id, const Vector2& position, int x, int y, int w, int h);
	void DrawPartExtend(const SPRITE_ID& id, const Vector2& position,const Vector2& exposition, int x, int y, int w, int h);
	void DrawPartRota(const SPRITE_ID& id, const Vector2& position,int x, int y, int w, int h,const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, float angle = 0.0f);


private:
	// �ʏ�摜
	std::unordered_map<SPRITE_ID, int> m_sprites;

	std::unordered_map<SPRITE_ID, std::vector<int>> m_divSprites;

};