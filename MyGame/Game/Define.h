#pragma once
//ゲームシステム上のパラメータ

static const float BGMVOLUME = 0.5f;
static const float SEVOLUME = 0.5f;

static int constexpr WINDOW_WIDTH = 1920;
static int constexpr WINDOW_HEIGHT = 1080;

static int constexpr SPACE_DEPTH = 5 - 1;//深度は0～nの範囲を取る

static int constexpr GRID_X = 10;
static int constexpr GRID_Y = 10;

static constexpr int SEGMENT_VERTEX_COUNT = 2;

static constexpr float FarSpeed = 2.0f;
static constexpr int PlayerHP = 10;
static constexpr int SetGunPoint = 7;
