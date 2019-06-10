#include "EffekseerEffect.h"

#include <EffekseerForDXLib.h>

#include "../Math/MathHelper.h"

int EffekseerEffect::m_effect{ -1 };
EffectAsset EffekseerEffect::asset_;

void EffekseerEffect::initialize()
{
	finalize();
}

void EffekseerEffect::finalize()
{
	asset_.clear();
	m_effect = -1;
}

bool EffekseerEffect::load(int id, const std::string & file_name)
{
	return asset_.load(id, file_name);
}

void EffekseerEffect::erase(int id)
{
	m_effect = (m_effect == asset_[id]) ? -1 : m_effect;
	asset_.erase(id);
}

void EffekseerEffect::bind(int id)
{
	m_effect = asset_[id];
}

int EffekseerEffect::play()
{
	return PlayEffekseer3DEffect(m_effect);
}

void EffekseerEffect::draw()
{
	DrawEffekseer3D();
}
