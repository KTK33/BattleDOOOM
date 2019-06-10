#include "EffectAsset.h"

#include <EffekseerForDXLib.h>

EffectAsset::EffectAsset()
{
}

EffectAsset::~EffectAsset()
{
	clear();
}

bool EffectAsset::load(int id, const std::string & file_name)
{
	erase(id);
	asset_[id] = LoadEffekseerEffect(file_name.c_str());
	return asset_[id] != -1;
}

void EffectAsset::erase(int id)
{
	if (asset_.count(id) > 0)
	{
		DeleteEffekseerEffect(asset_[id]);
		asset_.erase(id);
	}
}

void EffectAsset::clear()
{
	for (const auto eff : asset_)
		DeleteEffekseerEffect(eff.second);

	asset_.clear();
}

int EffectAsset::operator[](int id) const
{
	return asset_.at(id);
}
