#pragma once
#include "../EffekseerEffect/EffekseerEffect.h"

class EffectObj
{
public:
	//�R���X�g���N�^
	EffectObj(int l_effect);

	//�X�V
	void update(float deltaTime);

	//�`��
	void draw()const;

	void play();

	void stop();

	void set_position(Vector3 l_position);

	void set_rotation(float x, float y, float z);

	void set_scale(Vector3 l_scale);

	void change_effect(int l_effect);

	int get_isPlaying()const;

private:
	int m_effect;
	int m_playingEff;
};