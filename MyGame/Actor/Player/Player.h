#pragma once

#include "../Actor.h"
#include "../../Collision/BoundingCapsule.h"
#include "../../Mesh/SkeletalMesh.h"
#include "../../Mesh/StaticMesh.h"
#include "../../Animation/Animation.h"
#include "../../Animation/AnimationMesh.h"
#include "PlayerState.h"
#include "../../World/World.h"

class Player : public Actor {
public:
	Player(int model,int weapon,IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{0.0f,5.0f,0.0f},Matrix::Identity,15.0f,4.0f));

	virtual void initialize() override;

	void update(float deltaTime);

	void draw() const;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//状態の更新
	void update_state(float delta_time);
	//状態の変更
	void change_state(PlayerState::State state, int motion);
	//移動処理
	void move(float delta_time);
	//パンチ
	void punch(float delta_time);
	//キック
	void kick(float delta_time);
	//剣
	void sword(float delta_time);
	//銃
	void gun(float delta_time);
	//ダメージ中
	void damage(float delta_time);
	//ジャンプ中
	void jump(float delta_time);
	//武器の描画
	void draw_weapon() const;



private:
	//World world__;
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	//モーション番号
	int motion_;
	//持ち物モデル
	int weapon_;
	//移動速度
	const float WalkSpeed{ 0.25f };
	//状態
	PlayerState::State state_;
	//状態タイマ
	float state_timer_;
	//重力
	const float Gravity{ -0.04f };

	//残弾数
	int RemainGun;

	//ディレイタイム
	int DelayGunTime;

};


//モーション番号
enum
{
	MotionIdel = 0,
	MotionForwardWalk = 1,
	MotionBackarWalk = 1,
	MotionLeftWalk = 1,
	MotionRightWalk = 1,
	MotionPunch = 4,
	MotionKick = 5,
	MotionGun = 7,
	MotionSword = 6,
	MotionDamage = 8,
	MotionJump = 3
};
