#pragma once

#include <Dxlib.h>
#include <array>
#include <string>
#include <unordered_map>
#include <list>
#include "SoundID.h"
class Sound
{
private:
	Sound();
	~Sound();

public:
	static Sound &GetInstance() {
		static Sound s;
		return s;
	}

	///<summary>
	/// 初期化処理
	///</summary>
	void Initialize();

	///<summary>
	/// BGMを読み込む
	///</summary>
	void LoadBGM(const std::string& filename, const BGM_ID& id, float volume = 1.0f);
	///<summary>
	/// SEを読み込む
	///</summary>
	void LoadSE(const std::string& filename, const SE_ID& id, float volume = 1.0f);
	///<summary>
	/// 3D(立体音響)で再生したいSEを読み込む
	///</summary>
	void Load3DSE(const std::string& filename, const SE_ID& id, float volume = 1.0f);

	int DuplicateSE(SE_ID id)const;

	///<summary>
	/// 読み込んだBGM、SEをすべて削除する
	///</summary>
	void DeleteAll();
	///<summary>
	/// BGMを鳴らす
	///</summary>
	void PlayBGM(const BGM_ID& id, int playtype = DX_PLAYTYPE_BACK);
	///<summary>
	/// SEを鳴らす
	///</summary>
	void PlaySE(const SE_ID& id, int playtype = DX_PLAYTYPE_BACK);
	void PlaySE(int id, int playtype = DX_PLAYTYPE_BACK);

	void Play3DSE(const SE_ID& id, VECTOR* position, int playtype = DX_PLAYTYPE_BACK);
	///<summary>
	/// SEを指定の長さにセットする
	///</summary>
	void SetRate(const SE_ID& id, int rate);
	///<summary>
	/// SEをデフォルトの長さにセットする
	///</summary>
	void ReSetRate(const SE_ID& id);
	///<summary>
	/// SEの長さを取得する
	///</summary>
	int GetRate(const SE_ID& id);
	//指定音が鳴っているかのチェックを行い、鳴ってなかったら再生
	void PlaySE_IsNotPlay(const SE_ID& id);
	void PlaySE_IsNotPlay(int id);
	///<summary>
	/// 同一SEが重ならないように鳴らす
	///</summary>
	int PlaySEDuplicate(const SE_ID& id, int playtype = DX_PLAYTYPE_BACK);
	///<summary>
	/// BGMを止める
	///</summary>
	void StopBGM();
	///<summary>
	/// SEを止める
	///</summary>
	void StopSE(const SE_ID& id);
	void StopSE(int id);
	void StopSE();

	///<summary>
	/// BGMが鳴っているかどうか調べる
	///</summary>
	bool IsPlayBGM();
	///<summary>
	/// SEが鳴っているかどうか調べる
	///</summary>
	bool IsPlaySE(const SE_ID& id);
	bool IsPlaySE(int id);

	///<summary>
	/// 各BGMのボリュームを設定する
	///</summary>
	void SetBGMVolume(const BGM_ID& id, float volume);
	///<summary>
	/// 各SEのボリュームを設定する
	///</summary>
	void SetSEVolume(const SE_ID& id, float volume);
	///<summary>
	/// 各BGMのボリュームを受け取る
	///</summary>
	float IsBGMVolume(const BGM_ID& id);
	///<summary>
	/// 各SEのボリュームを受け取る
	///</summary>
	float IsSEVolume(const SE_ID& id);

	///<summary>
	/// 全てのBGMのボリュームを設定する
	///</summary>
	void SetAllBGMVolume(float volume);
	///<summary>
	/// 全てのSEのボリュームを設定する
	///</summary>
	void SetAllSEVolume(float volume);
	///<summary>
	/// 全てのBGMのボリュームを受け取る
	///</summary>
	float IsAllBGMVolume();
	///<summary>
	/// 全てのSEのボリュームを受け取る
	///</summary>
	float IsAllSEVolume();

	void SetEventListenerPos(const VECTOR& position, const VECTOR& forward);

	int GetCountBGM()
	{
		return static_cast<int>(m_BGMs.size());
	}
	int GetCountSE()
	{
		return static_cast<int>(m_SEs.size());
	}
	int GetHandle(SE_ID id)const {
		return m_SEs.at(id);

	}
	void Update();

	Sound(const Sound& other) = delete;
	Sound& operator = (const Sound& other) = delete;

private:
	std::string Split(const std::string& filename);

private:
	void SettingBGM(const BGM_ID& id);

	void SettingSE(const SE_ID& id);

	std::list<std::pair<SE_ID, VECTOR*>> _play3DSoundList;

	std::unordered_map<BGM_ID, int> m_BGMs;				// BGMハンドル
	std::unordered_map<SE_ID, int> m_SEs;				// SEハンドル
	std::unordered_map<BGM_ID, float> m_BGM_Volumes;	// 各BGMボリューム
	std::unordered_map<SE_ID, float> m_SE_Volumes;		// 各SEボリューム
	float m_bgm_volume;									// 全BGMボリューム
	float m_se_volume;									// 全SEボリューム

	std::array<int, 512>				dupSE;			// 同時再生可能SE
};