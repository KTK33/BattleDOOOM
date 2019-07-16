#pragma once

///シューティングモードのプレイヤーのデータ

//プレイヤーの最大ＨＰ
static constexpr int ShootingPlayerHPVal = 10;

//初期に持っている弾数
static const int InitHaveGun = 30;

//一度にセットできる弾数
static const int SetGunPoint = 7;

//弾を拾ったときに取得できる弾数
static const int GetBulletPoint = 10;

//回復アイテムを拾ったときの回復量
static const int GetHpPoint = 3;

//初期にもっている回復アイテムの数
static const int HaveRecoverItem = 3;

//初期に持っている攻撃アップの数
static const int HaveAttackUpItem = 1;

//敵の落とすアイテムの割合(0～100) 値が大きいほど弾が落ちやすい、0に近いほど回復アイテムが落ちやすい　100に近いほど弾が落ちやすい
static const int GetItemRate = 70;

//攻撃アップアイテムを使ったときの継続時間(秒)
static const int AttackUpTime = 30;

//弾の速度
static const float BulletSpeed = 10.0f;

//通常の銃での攻撃力
static const int NormalAttackVal = 1;

//攻撃アップ中の銃での攻撃力
static const int UPAttackVal = 2;

//パンチの攻撃力
static const int PunchAttackVal = 1;

//移動速度(エイム状態でない)
static const float OutAimWalkSpeed = 0.8f;

//後左右に移動しているときの速度倍率

static const float BackRightLeftWalk = 0.3f;

//移動速度(エイム状態中)
static const float IAimWalkSpeed = 0.5f;

//エイム状態でないときにどれくらいスティックを倒すと歩きモーションが走りモーションになるのか
static const float OutAimWalkRunVal = 0.75f;

//アイテムをゲットしたのテキストの表示時間(秒)
static const int TextTime = 1;
