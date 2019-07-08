#pragma once

///アクションモードのプレイヤーのデータ

//HP
static const int ActionPlayerHPVal = 10;

//移動速度
static const float ActionPlayerSpeedVal = 1.0f;

//どれくらいスティックを倒すと歩きモーションが走りモーションになるのか
static const float WalkRunVal = 0.8f;

//走りモーションになったときに加算される移動速度
static const float ActionPlayerRunSpeedVal = 0.5f;

//回避加速度
static const float mAvoidanceSpeed = 0.5f;
