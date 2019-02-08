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

	void initialize() override;

	void update(float deltaTime);

	void draw() const;

	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//壁と床の判定
	void collision();

	//状態の更新
	void update_state(float deltaTime);
	//状態の変更
	void change_state(PlayerState::State state, int motion);
	void PlayerInput();
	void Idle();
	void IdletoAim();
	void AimtoIdle();
	void IdleAiming();
	void StopGun();
	void Reload();
	void GunPunch();
	void GunMove(float X,float Y);
	void Move(float X, float Y);
	void Gun(PlayerState::State state);
	void Damage();
	void Dead();
	//武器の描画
	void draw_weapon() const;
	//ディレイ系
	void Delay();



private:
	//World world__;
	//アニメーションメッシュ
	AnimatedMesh mesh_;
	//モーション番号
	int motion_;
	int before_motion_;
	//持ち物モデル
	int weapon_;
	//移動速度
	const float WalkSpeed{ 0.25f };
	//状態
	PlayerState::State state_;
	PlayerState::State before_state_;
	//状態タイマ
	float state_timer_;
	//重力
	const float Gravity{ -0.04f };

	//残弾数
	int SetRemainGun;
	//ディレイタイム
	int DelayGunTime;
	bool CheckGun;

	int invinciblyTime;
	bool invinciblyCheck;

	int weaponPos;
};


//モーション番号
enum
{
	MotionPlayerIdel = 0,
	MotionPlayerStopGun = 1,
	MotionPlayerForwardGun = 2,
	MotionPlayerRightGun = 3,
	MotionPlayerLeftGun = 4,
	MotionPlayerBackGun = 5,
	MotionPlayerReload = 6,
	MotionPlayerIdleToAim = 7,
	MotionPlayerAimToIdle = 8,
	MotionPlayerIdle2 = 9,
	MotionPlayerDamageGun = 10,
	MotionPlayerDead = 11,
	MotionPlayerGunPunch = 12,
	MotionPlayerRun = 13,
	MotionPlayerIdleAiming = 14,
	MotionPlayerDamage = 15,
};
