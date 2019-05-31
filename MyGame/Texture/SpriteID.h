#pragma once

enum class SPRITE_ID
{
	FADEBLACK,
	//タイトル画面
	TITLEBACK,
	TITLENAME,
	TITLENAMEBACK,
	TITLEPRESS_START,
	TITLEBACKWHITE,
	TITLECHUI,
	TITLEJIKYO,

	//セレクト画面
	SELECTBACK,
	SELECT_SHOOTING,
	SELECT_SHOOTING_DEC,
	SELECT_SHOOTING_EX,
	SELECT_ACTION,
	SELECT_ACTION_DEC,
	SELECT_ACTION_EX,
	SELECT_NAME,

	//プレイ画面
	TEXTFRAME,
	TEXTBOSSAPPEAR,
	TEXTDUMMYDEAD,
	HP_UI,
	HP_GAUGE,
	NUMBER,
	MISSION_NUMBER,
	THRASH,
	GUN_FREAM,
	HPRECOVERTEXT,
	HPRECOVERUI,
	BULLETGETUI,
	BOSSHP_UI,
	BOSSHP_GAUGE,
	ENEMY_COUNT_ATO,
	MISSION_ENEMY_EXTERMINATION,
	MISSION_BOSS_DEFEAT,
	SIGHT,
	ITEMBOX,
	GAMEOVERBACK,
	GAMEOVERNAME,
	GAMECLEARBACK,
	GAMECLEARNAME,
	BULLET_EMPTY,
	ATTACK_UPNOW,

	//ポーズ画面
	PAUSEBACK,
	ITEM,
	PAUSEITEM,
	PAUSEITEM_DESCRIPTION,
	OPERATION,
	PAUSEOPERATION,
	PAUSEOPERATION_DESCRIPTION,
	PAUSEITEM_TUKAU,
	PAUSEITEM_TUKAUBACK,
	SYSTEM,
	PAUSESYSTEM,
	PAUSESYSTEM_DESCRIPTION,
	PAUSESYSTEM_FREAM,
	PAUSESYSTEM_FREAMS,
	PAUSESYSTEM_CURSOR,
	PAUSETITLE,
	PAUSETITLE_DESCRIPTION,

	//エフェクト
	EFFECT_BULLETHIT,

	//アクションモードポーズ画面
	ACTIONPAUSE_BACK,
	ACTIONPAUSE_OPERATION,
	ACTIONPAUSE_OPERATION_UI,
	ACTIONPAUSE_TITLEBACK,
	ACTIONPAUSE_CURSOR,

	//アクションモード
	ACTION_PLAYER_HPFRAME,
	ACTION_PLAYER_HPGAUGE,
	REDSAMURAI_HPFRAME,
	REDSAMURAI_HPGAUGE,
	ACTIONPLAYERDEAD,
	REDSAMURAIDEAD,
	KAKUGOWO,
	MOTTOREISEINI,
	KOKODEHIKU,
};