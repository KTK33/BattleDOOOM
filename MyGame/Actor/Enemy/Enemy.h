#ifndef ENEMY_H_
#define ENEMY_H_

#include "../../Mesh/SkeletalMesh.h"
#include "../../Mesh/StaticMesh.h"
#include "../../Graphics/Graphics3D.h"
#include "../../Input/GamePad.h"
#include "../../Math/MathH.h"
#include "../Player/Player.h"
#include "../../Animation/Animation.h"
#include "../../Animation/AnimationMesh.h"
#include "../Actor.h"

//敵のモーション番号
enum
{
	EnemyMotionIdle = 0,
	EnemyMotionWalk = 1,
	EnemyMotionTurnLeft = 2,
	EnemyMotionTurnRight = 3,
	EnemyMotionDamage = 4,
	EnemyMotionAttack = 5,
	EnemyMotionDead = 6
};

//敵クラス
class Enemy : public Actor {
public:
	enum class State
	{
		Idle,     //アイドル状態
		Walk,     //歩き
		Turn,     //振り向き
		Damage,   //ダメージ
		Attack    //攻撃
	};

public:
	//コンストラクタ
	Enemy(int model, const Vector3& position,IWorld& world);
	//更新
	virtual void update(float delta_time);
	//描画
	virtual void draw() const;
	//衝突処理
	virtual void react(Actor& other) override;
	//行列の取得
	//Matrix pose() const;

private:
	//状態の更新
	void update_state(float delta_time);
	//状態の変更
	void change_state(State state, int motion);
	//アイドル状態
	void idle(float delta_time);
	//移動中
	void walk(float delta_time);
	//振り向き中
	void turn(float delta_time);
	//攻撃中
	void attack(float delta_time);
	//ダメージ中
	void damage(float delta_time);
	//振り向き判定
	bool is_turn() const;
	//攻撃判定
	bool is_attack() const;
	//移動判定
	bool is_walk() const;
	//ターゲット方向の角度を求める
	float target_angle() const;
	//ターゲットの距離を求める
	float target_distance() const;

private:
	////向き
	//Matrix rotation_;
	////座標
	//Vector3 position_;
	////移動量
	//Vector3 velocity_;
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	//モーション番号
	int motion_;
	//状態
	State state_;
	//状態タイマ
	float state_timer_;
	//プレイヤー
	Actor* player_;
	
	int timer_;

	//振り向き距離
	const float TurnDistance{ 15.0f };
	//攻撃範囲
	const float AttackDistance{ 12.0f };
	//移動スピード
	const float WalkSpeed{ 0.25f };
	//振り向く角度
	const float TurnAngle{ 2.5f };
};


#endif // !ENEMY_H_

