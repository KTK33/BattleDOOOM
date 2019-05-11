#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationMesh.h"
#include "../PlayerState.h"
#include "../World/World.h"
#include "../Actor/ActorSystem/ActorSystem.h"

class Player : public Actor,public ActorSystem{
public:
	Player(int model,int weapon,IWorld* world, const Vector3& position, std::weak_ptr<Actor> ui,const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{0.0f,9.0f,0.0f},Matrix::Identity,10.0f,4.0f));
	virtual ~Player() override{}

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

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
	void Reload();
	void GunPunch();
	void GunMove(float X,float Y);
	void Move(float X, float Y);
	void Gun();
	void PlayerGunFire();
	void JumpChacker(PlayerState::State state);
	void Jump();
	void Damage();
	void Dead();
	void Tyohatu();
	//武器の描画
	void draw_weapon() const;
	//ディレイ系
	void Delay();

	void Hit(Vector3& dir);
private:
	std::weak_ptr<Actor> m_ui{};
	IBodyPtr Initbody;
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

	//状態,
	PlayerState::State state_;
	PlayerState::State before_state_;
	//状態タイマ
	float state_timer_;
	//重力
	const float Gravity{ -0.04f };

	//残弾数(セットされている)
	int SetRemainGun;
	//現在持っている弾数
	int HaveGun;
	//ディレイタイム
	int DelayGunTime;

	int invinciblyTime;
	bool invinciblyCheck;

	int weaponPos;

	Vector3 AimPos;
	Vector3 InitAimPos;

	int RecoverItemCount;
	int AttackItemCount;

	int alreadyItem;

	bool DeadCheck;

	bool GunPossible;

	int AttackParam;
	bool AttackUpCheck;
	int AttackUpTime;
};
