#include "Sound.h"
#include "../Game/Define.h"
#include "../math/MathHelper.h"
#include <sstream>

static constexpr float SOUND_RANGE = 256.0f;

Sound::Sound() :
	m_bgm_volume(0.5f), m_se_volume(0.7f)
{

}

Sound::~Sound()
{
	InitSoundMem();
}

// 初期化処理
void Sound::Initialize()
{

	InitSoundMem();
	m_BGMs.clear();
	m_SEs.clear();
	_play3DSoundList.clear();
	Set3DSoundOneMetre(10.0f);

	//dupSE.clear();
	for (auto& se : dupSE)
	{
		se = 0;
	}
}

// BGMを読み込む
void Sound::LoadBGM(const std::string& filename, const BGM_ID& id, float volume)
{
	m_BGMs[id] = LoadSoundMem(filename.c_str());
	m_BGM_Volumes[id] = volume;
	SettingBGM(id);
}

// SEを読み込む
void Sound::LoadSE(const std::string& filename, const SE_ID& id, float volume)
{
	m_SEs[id] = LoadSoundMem(filename.c_str());
	m_SE_Volumes[id] = volume;
	SettingSE(id);
}

// 3D(立体音響)で再生したいSEを読み込む
void Sound::Load3DSE(const std::string& filename, const SE_ID& id, float volume)
{
	SetCreate3DSoundFlag(TRUE);
	m_SEs[id] = LoadSoundMem(filename.c_str());
	m_SE_Volumes[id] = volume;
	SetCreate3DSoundFlag(FALSE);

	Set3DRadiusSoundMem(SOUND_RANGE, m_SEs[id]);

	SettingSE(id);
}

int Sound::DuplicateSE(SE_ID id) const
{
	return DuplicateSoundMem(m_SEs.at(id));
}

void Sound::DeleteAll()
{
	std::unordered_map<BGM_ID, int>::iterator bgmitr = m_BGMs.begin();
	while (bgmitr != m_BGMs.end()) {
		DeleteSoundMem(bgmitr->second);
		++bgmitr;
	}
	m_BGMs.clear();

	std::unordered_map<SE_ID, int>::iterator seitr = m_SEs.begin();
	while (seitr != m_SEs.end()) {
		DeleteSoundMem(seitr->second);
		++seitr;
	}
	m_SEs.clear();

	m_BGM_Volumes.clear();
	m_SE_Volumes.clear();
}

// ファイル名の'.'から後を取り除く
std::string Sound::Split(const std::string& filename)
{
	std::string assetname;
	std::getline(
		std::stringstream(filename),
		assetname,
		'.'
	);
	return assetname;
}

// BGMを鳴らす
void Sound::PlayBGM(const BGM_ID& id, int playtype)
{
	PlaySoundMem(m_BGMs[id], playtype);
}

// SEを鳴らす
void Sound::PlaySE(const SE_ID& id, int playtype)
{
	PlaySE(m_SEs[id], playtype);
}

void Sound::PlaySE(int id, int playtype)
{
	if (IsPlaySE(id) && playtype == DX_PLAYTYPE_LOOP)
		return;

	ChangeVolumeSoundMem(static_cast<int>(((m_se_volume /** id*/)) * 255), id);
	PlaySoundMem(id, playtype);
}

void Sound::Play3DSE(const SE_ID & id, VECTOR* position, int playtype)
{
	Set3DPositionSoundMem(*position, m_SEs[id]);

	PlaySE(id, playtype);

	_play3DSoundList.push_back(std::make_pair(id, position));
}

void Sound::SetRate(const SE_ID & id, int rate)
{
	SetFrequencySoundMem(rate, m_SEs[id]);
}

void Sound::ReSetRate(const SE_ID & id)
{
	ResetFrequencySoundMem(m_SEs[id]);
}

int Sound::GetRate(const SE_ID & id)
{
	return GetFrequencySoundMem(m_SEs[id]);
}

void Sound::PlaySE_IsNotPlay(const SE_ID & id)
{
	PlaySE_IsNotPlay(m_SEs[id]);
}

void Sound::PlaySE_IsNotPlay(int id)
{
	if (IsPlaySE(id))return;

	PlaySE(id);
}

int Sound::PlaySEDuplicate(const SE_ID& id, int playtype)
{
	if (IsPlaySE(id) && playtype == DX_PLAYTYPE_LOOP)
		return -1;

	ChangeVolumeSoundMem(static_cast<int>(((m_se_volume * m_SE_Volumes[id])) * 255), m_SEs[id]);
	int dupHandle = DuplicateSoundMem(m_SEs[id]);
	PlaySoundMem(dupHandle, playtype);

	for (auto& se : dupSE)
	{
		if (se == 0)
		{
			se = dupHandle;
			return dupHandle;
		}
	}
	return dupHandle;
}

// BGMを止める
void Sound::StopBGM()
{
	for (auto i : m_BGMs)
	{
		StopSoundMem(i.second);
	}
}

// SEを止める
void Sound::StopSE(const SE_ID& id)
{
	StopSE(m_SEs[id]);
}

void Sound::StopSE(int id)
{
	StopSoundMem(id);
}

void Sound::StopSE()
{
	for (auto i : m_SEs)
	{
		StopSoundMem(i.second);
	}
}

// BGMが鳴っているかどうか調べる
bool Sound::IsPlayBGM()
{
	for (auto i : m_BGMs)
	{
		if (CheckSoundMem(i.second))
		{
			return true;
		}
	}
	return false;
}

// SEが鳴っているかどうか調べる
bool Sound::IsPlaySE(const SE_ID& id)
{
	return IsPlaySE(m_SEs[id]);
}

bool Sound::IsPlaySE(int id)
{
	return CheckSoundMem(id) == 1;
}

// 各BGMのボリュームを設定する
void Sound::SetBGMVolume(const BGM_ID& id, float volume)
{
	m_BGM_Volumes[id] = volume;
	SettingBGM(id);
}

// 各SEのボリュームを設定する
void Sound::SetSEVolume(const SE_ID& id, float volume)
{
	m_SE_Volumes[id] = volume;
	SettingSE(id);
}

// 各BGMのボリュームを受け取る
float Sound::IsBGMVolume(const BGM_ID& id)
{
	return m_BGM_Volumes[id];
}

// 各SEのボリュームを受け取る
float Sound::IsSEVolume(const SE_ID& id)
{
	return m_SE_Volumes[id];
}

// 全てのBGMのボリュームを設定する
void Sound::SetAllBGMVolume(float volume)
{
	m_bgm_volume = volume;
	for (auto& i : m_BGMs)
		SettingBGM(i.first);
	m_bgm_volume = MathHelper::Clamp(m_bgm_volume, 0.0f, 1.0f);
}

// 全てのSEのボリュームを設定する
void Sound::SetAllSEVolume(float volume)
{
	m_se_volume = volume;
	for (auto& i : m_SEs)
		SettingSE(i.first);
	m_se_volume = MathHelper::Clamp(m_se_volume, 0.0f, 1.0f);
}

// 全てのBGMのボリュームを受け取る
float Sound::IsAllBGMVolume()
{
	return m_bgm_volume;
}

// 全てのSEのボリュームを受け取る
float Sound::IsAllSEVolume()
{
	return m_se_volume;
}

void Sound::SetEventListenerPos(const VECTOR& position, const VECTOR& forward)
{

	Set3DSoundListenerPosAndFrontPos_UpVecY(position, forward);
}

void Sound::Update()
{
	for (auto& se : dupSE)
	{
		if (CheckSoundMem(se) == 0 && se != 0)
		{
			DeleteSoundMem(se);
			se = 0;
		}
	}
	_play3DSoundList.remove_if([&](auto& sound) {return (!IsPlaySE(sound.first)) || (sound.second == nullptr); });
	for (auto& s : _play3DSoundList) {
		auto c = *s.second;
		Set3DPositionSoundMem(*s.second, m_SEs[s.first]);
	}
}

void Sound::SettingBGM(const BGM_ID& id)
{
	ChangeVolumeSoundMem(static_cast<int>(((m_bgm_volume * m_BGM_Volumes[id])) * 255), m_BGMs[id]);
}

void Sound::SettingSE(const SE_ID& id)
{
	ChangeVolumeSoundMem(static_cast<int>(((m_se_volume * m_SE_Volumes[id])) * 255), m_SEs[id]);
}