#pragma once
#include "../EffectAsset/EffectAsset.h"
#include "../Math/Vector3.h"

class EffekseerEffect
{
public:
	//������
	static void initialize();

	//�I������
	static void finalize();

	//�ǂݍ���
	static bool load(int id, const std::string& file_name);

	//�폜
	static void erase(int id);

	//�o�C���h
	static void bind(int id);

	static int play();

	//�`��
	static void draw();

private:
	static int m_effect;
	static EffectAsset asset_;
};