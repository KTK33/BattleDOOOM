#pragma once

#include "../../Actor.h"

class ShootingCamera : public Actor
{
public:
	ShootingCamera(IWorld* world, std::weak_ptr<Actor> m_Player);

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	//ばね
	void move(
		const Vector3& rest_position, //ばねの静止位置
		float stiffness,                //ばね定数(ばねの強さ)
		float friction,                 //摩擦力
		float mass                      //質量
	);

	//カメラの設定
	void CameraSet(float deltaTime);

	//プレイヤーの入力情報
	void Aim_Input();

	//エイム外
	void Out_Aim();

	//エイム中
	void In_Aim();

	//エイム中のカメラ向き
	void In_Aim_Rotation();

	//ゲーム終了時設定
	void PlayerGameFinish();

	//ゲームオーバー
	void GameOver();

	//ゲームクリア
	void GameClear();


private:
	Actor* mplayer_;
	//
	Vector3 mtarget_{ 0.0f,0.0f,0.0f };

	Vector2 mFarPoint{ 30.f,20.f };

	float mangle{ 0 };

	Vector2 mAimPosMove;

	std::weak_ptr<Actor> mplayer{};

	Vector3 mDeadCamera{ 20,20,20 };
	bool malreadyGO;
};