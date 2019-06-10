#include "EffectObj.h"

#include <EffekseerForDXLib.h>
#include "../Math/MathHelper.h"

EffectObj::EffectObj(int l_effect)
	:m_effect{ l_effect }
{
	m_playingEff = -1;
}

void EffectObj::update(float speed)
{
	if (m_playingEff != -1)
	{
		SetSpeedPlayingEffekseer3DEffect(m_playingEff, speed);
		m_time -= speed;
		if (m_time < 0)
		{
			stop();
			m_time = 0;
		}
	}
	UpdateEffekseer3D();
}

void EffectObj::draw() const
{
	EffekseerEffect::bind(m_effect);
	EffekseerEffect::draw();
}

void EffectObj::play()
{
	EffekseerEffect::bind(m_effect);
	m_playingEff = EffekseerEffect::play();
}

void EffectObj::stop()
{
	if (m_playingEff != -1)
	{
		StopEffekseer3DEffect(m_playingEff);
		m_playingEff = -1;
	}		
}

void EffectObj::set_position(Vector3 l_position)
{
	if (m_playingEff != -1)
		SetPosPlayingEffekseer3DEffect(m_playingEff, l_position.x, l_position.y, l_position.z);
}

void EffectObj::set_rotation(Vector3 lrota)
{
	if (m_playingEff != -1)
		SetRotationPlayingEffekseer3DEffect(m_playingEff, MathHelper::ToRadians(lrota.x), MathHelper::ToRadians(lrota.y), MathHelper::ToRadians(lrota.z));
}

void EffectObj::set_scale(Vector3 l_scale)
{
	if (m_playingEff != -1)
		SetScalePlayingEffekseer3DEffect(m_playingEff, l_scale.x, l_scale.y, l_scale.z);
}

void EffectObj::change_effect(int l_effect)
{
	m_effect = l_effect;
}

int EffectObj::get_isPlaying() const
{
	return IsEffekseer3DEffectPlaying(m_playingEff);
}

void EffectObj::set_endTime(float time)
{
	m_time = time;
}
