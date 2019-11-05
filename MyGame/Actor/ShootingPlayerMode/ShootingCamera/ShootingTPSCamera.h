#pragma once

#include "../Actor/Actor.h"
#include "../Actor/ShootingPlayerMode/UIActor/SightUI/SightUI.h"

//シューティングモードのTPSカメラ
class ShootingTPSCamera : public Actor
{
public:
	ShootingTPSCamera(IWorld* world, std::weak_ptr<Actor> m_Player);
	virtual ~ShootingTPSCamera()override {}

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	void PlayerInput(float deltaTime);

	virtual void receiveMessage(EventMessage message, void * param) override;

private:
	//ゲーム終了時設定
	void PlayerGameFinish();

	//次のシーンのタイプ
	void NextSceneType(int type);

private:
	Actor* player_;
	//
	Vector3 target_{ 0.0f,0.0f,0.0f };

	std::weak_ptr<Actor> m_player{};

	//ターゲットからのオフセット
	Vector3 mOffset;
	//カメラの上方向ベクトル
	Vector3 mUp;
	//ピッチの角速度
	float mPitchSpeed;
	//ヨーの角速度
	float mYawSpeed;
	//前方向
	Vector3 mForward;

	//プレイヤーの高さ
	int PlayerHeight{ 15 };

	SightUI mSU;

	//
	Vector3 mFinishCamera;
	bool malreadyCreate;
};