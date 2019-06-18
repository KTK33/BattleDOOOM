#pragma once

///アクションモードの赤侍のデータ

//HP
static const int RedSamuraiHPVal = 15;

//移動速度
static const float RedSamuraiMoveSpeed = 0.75f;

//攻撃する頻度(秒)
static const int RedSamuraiAttackTime = 1;

//連続攻撃１撃目の攻撃力
static const int SwardAttack1Val = 1;

//連続攻撃２撃目の攻撃力
static const int SwardAttack2Val = 2;

//連続攻撃３撃目の攻撃力
static const int SwardAttack3Val = 3;

//振り下ろし攻撃の攻撃力
static const int SwardDownVal = 5;

//弓攻撃の攻撃力
static const int ArrowAttackVal = 1;

//プレイヤーまでの距離がこの値以下の時に弓攻撃になる値
static const float ArrowTypeDis = 15.0f;

//連続攻撃になる割合(1〜10) 10に近いほど連続攻撃になる
static const int AttackTypeRate = 7;

//プレイヤーの距離がこの値以下になると戦闘体制になる
static const float AttackStartDis = 100.0f;