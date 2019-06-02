#include "EffectObj.h"
#include <EffekseerForDXLib.h>
#include "../Math/MathHelper.h"

EffectObj::EffectObj(int l_effect)
	:m_effect{ l_effect }
{
	m_playingEff = -1;
}

void EffectObj::update(float deltaTime)
{
	if (m_playingEff != -1)
		SetSpeedPlayingEffekseer3DEffect(m_playingEff, deltaTime);
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

void EffectObj::set_rotation(float x, float y, float z)
{
	if (m_playingEff != -1)
		SetRotationPlayingEffekseer3DEffect(m_playingEff, MathHelper::ToRadians(x), MathHelper::ToRadians(y), MathHelper::ToRadians(z));
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
