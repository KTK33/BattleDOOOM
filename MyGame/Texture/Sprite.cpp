#include "Sprite.h"
#include"../Game/Define.h"

#include<DxLib.h>

Vector2 Sprite::GetSize(const SPRITE_ID & id) const
{
	int x, y;
	GetGraphSize(m_sprites.at(id), &x, &y);
	return Vector2{ (float)x,(float)y };
}

Vector2 Sprite::GetSizeDiv(const SPRITE_ID & id) const
{
	if (m_divSprites.count(id) == 0) return Vector2::Zero;
	float x, y;
	GetGraphSizeF(m_divSprites.at(id).at(0), &x, &y);
	return Vector2{ x,y };
}

int Sprite::GetHandle(const SPRITE_ID & id) const
{
	return m_sprites.at(id);
}

void Sprite::DrawPart(const SPRITE_ID & id, const Vector2 & position, int x, int y, int w, int h)
{
	DrawRectGraphF(position.x, position.y, x, y, w, h, m_sprites[id], TRUE, FALSE);
}

void Sprite::DrawPartExtend(const SPRITE_ID & id, const Vector2 & position, const Vector2 & exposition, int x, int y, int w, int h)
{
	DrawRectExtendGraphF(position.x, position.y, exposition.x, exposition.y, x, y, w, h, m_sprites[id], TRUE);
}

void Sprite::DrawPartRota(const SPRITE_ID & id, const Vector2 & position, int x, int y, int w, int h, const Vector2 & origin, const Vector2 & scale, float angle)
{
	DrawRectRotaGraph3F(position.x, position.y, x, y, w, h, origin.x, origin.y, scale.x, scale.y, angle, m_sprites[id], TRUE);
}


Sprite::~Sprite()
{
	InitGraph();
	m_sprites.clear();
	m_divSprites.clear();
}

void Sprite::Initialize()
{
	InitGraph();
	m_sprites.clear();
	m_divSprites.clear();
}

void Sprite::Load(const std::string & filename, const SPRITE_ID & id)
{
	m_sprites[id] = LoadGraph(filename.c_str());
}

void Sprite::DivLoad(const std::string & filename, const SPRITE_ID & id, int spriteWidth, int spriteHeight, int divXSize, int divYSize, int divCount)
{
	int* temp = new int[divCount];

	LoadDivGraph(filename.c_str(), divCount, divXSize, divYSize, spriteWidth, spriteHeight, temp);
	m_sprites[id] = temp[0];
	for (int i = 0; i < divCount; i++) {
		m_divSprites[id].push_back(temp[i]);
	}

	delete[] temp;

}

void Sprite::DeleteAll()
{
	std::unordered_map<SPRITE_ID, int>::iterator spritr = m_sprites.begin();
	while (spritr != m_sprites.end()) {
		DeleteGraph(spritr->second);
		++spritr;
	}
	m_sprites.clear();

}

void Sprite::DrawSetCenter(const SPRITE_ID & id, const Vector2 & position)
{
	Draw(id, position, GetSize(id)*0.5f);
}

void Sprite::Draw(const SPRITE_ID & id, const Vector2 & position, const Vector2 & origin, const Vector2 & scale, float angle)
{
	DrawRotaGraph3((int)position.x, (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle, m_sprites[id], true);

}

void Sprite::DrawBillBoard(const SPRITE_ID & id, const Vector3 & position, const Vector2 & origin, float size, float angle)
{
	DrawBillboard3D(VGet(position.x, position.y, position.z), origin.x, origin.y, size, angle, m_sprites[id], TRUE);

}
#include"../Math/Vector3.h"
#include"../Math/Matrix.h"
void Sprite::Draw3D(SPRITE_ID id, const Vector2 & position, const Vector2& size, int r, int g, int b, int a, float startangle, float Xangle, float Zangle, float Zoffset) {
	//ƒQ[ƒW˜g‚Ì•`‰æî•ñ‚ð“ü—Í
	VERTEX_3D vec[4];
	Vector3 pos{ position.x,position.y,Zoffset };
	vec[0].pos = pos + Vector3{ -size.x,0.0f,size.y }*Matrix::CreateRotationY(startangle)*Matrix::CreateRotationX(Xangle)*Matrix::CreateRotationZ(Zangle);
	vec[1].pos = pos + Vector3{ size.x,0.0f,size.y }*Matrix::CreateRotationY(startangle)*Matrix::CreateRotationX(Xangle)*Matrix::CreateRotationZ(Zangle);
	vec[2].pos = pos + Vector3{ -size.x,0.0f,-size.y }*Matrix::CreateRotationY(startangle)*Matrix::CreateRotationX(Xangle)*Matrix::CreateRotationZ(Zangle);
	vec[3].pos = pos + Vector3{ size.x,0.0f,-size.y }*Matrix::CreateRotationY(startangle)*Matrix::CreateRotationX(Xangle)*Matrix::CreateRotationZ(Zangle);

	vec[0].r = r;
	vec[1].r = r;
	vec[2].r = r;
	vec[3].r = r;
	vec[0].g = g;
	vec[1].g = g;
	vec[2].g = g;
	vec[3].g = g;
	vec[0].b = b;
	vec[1].b = b;
	vec[2].b = b;
	vec[3].b = b;
	vec[0].a = a;
	vec[1].a = a;
	vec[2].a = a;
	vec[3].a = a;
	vec[0].u = 0.0f;
	vec[0].v = 0.0f;
	vec[1].u = 1.0f;
	vec[1].v = 0.0f;
	vec[2].u = 0.0f;
	vec[2].v = 1.0f;
	vec[3].u = 1.0f;
	vec[3].v = 1.0f;

	SetUseGraphZBuffer(m_sprites[id], TRUE);
	DrawPolygon3DBase(vec, 4, DX_PRIMTYPE_TRIANGLESTRIP, m_sprites[id], TRUE);
	SetUseGraphZBuffer(m_sprites[id], FALSE);
}

void Sprite::DrawDivSprite(const SPRITE_ID & id, const Vector2 & position, int divNum, const Vector2 & origin, const Vector2 & scale, float angle)
{
	if (divNum >= m_divSprites[id].size())return;

	DrawRotaGraph3((int)position.x, WINDOW_HEIGHT - (int)position.y, (int)origin.x, (int)origin.y,
		(double)scale.x, (double)scale.y, angle, m_divSprites[id].at(divNum), true);
}
