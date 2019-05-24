#pragma once

#include "../../Actor.h"

class ShootingCamera : public Actor
{
public:
	ShootingCamera(IWorld* world, std::weak_ptr<Actor> m_Player);

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	//カメラの設定
	void CameraSet(float deltaTime);

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
	//プレイヤーの情報検索用
	Actor* mGetplayer_;

	//プレイヤーへ情報伝達用
	std::weak_ptr<Actor> mplayer{};

	//カメラのターゲット
	Vector3 mtarget_{ 0.0f,0.0f,0.0f };

	//エイムの位置
	Vector2 mAimPosMove;

	//
	Vector3 mFinishCamera;
	bool malreadyCreate;
};