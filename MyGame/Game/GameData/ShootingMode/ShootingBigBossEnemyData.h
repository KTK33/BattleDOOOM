#pragma once

///シューティングモードの大ボスエネミーのデータ

//HP
static const int BigBossHPVal = 20;

//移動速度
static const float BigBossWalkSpeed = 1.1f;

//出現してからの最初に攻撃を繰り出すまでの時間(秒)
static int BigBossInitDelayTime = 3;

//攻撃の頻度(秒)　硬直時間を引く(3なら 3 - 2 秒)
static int BigBossAttackTime = 3;

//攻撃後の硬直時間(秒)
static int BigBossDelayTime = 2;
