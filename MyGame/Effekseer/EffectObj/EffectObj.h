#ifndef _EFFECT_OBJ_H_
#define _EFFECT_OBJ_H_

#include "../EffekseerEffect/EffekseerEffect.h"
#include "../EFFECT_ID.h"

class EffectObj
{
public:
	//�R���X�g���N�^
	EffectObj(int l_effect);

	//�X�V
	void update(float speed);

	//�`��
	void draw()const;

	void play();

	void stop();

	void set_position(Vector3 l_position);

	void set_rotation(Vector3 lrota);

	void set_scale(Vector3 l_scale);

	void change_effect(int l_effect);

	int get_isPlaying()const;

	void set_endTime(float time);

private:
	int m_effect;
	int m_playingEff;

	float m_time{ 0.0f };
};

#endif