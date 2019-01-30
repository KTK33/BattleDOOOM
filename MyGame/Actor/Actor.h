#ifndef ACTOR_H_
#define ACTOR_H_

#include "../Collision/Base/IBodyPtr.h"
#include "../Collision/Base/DummyBody.h"
#include "../World/IWorld.h"
#include <string>
#include <functional>
#include <memory>
#include <list>

#include "../Fiield/Field.h"
#include "../Math/MathH.h"
#include "../Game/Define.h"

class IWorld;
enum class EventMessage
{
	HIT_PLAYER,
	HIT_ENEMY,
	HIT_BALL,
	DEAD_ENEMY,
	DUMMY_DEAD_ENEMY,
	DEAD_DUMMY_ENEMY,
};
//アクタークラス
class Actor {
public:
	//コンストラクタ
	Actor();
	Actor(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body = std::make_shared<DummyBody>());
	Actor(IWorld* world, const std::string& name, const Vector3& position, const Matrix& rotation, const IBodyPtr& body = std::make_shared<DummyBody>());
	//仮想デストラクタ
	virtual ~Actor(){}
	//初期化
	virtual void initialize();
	//更新
	virtual void update(float delta_time);
	//描画
	virtual void draw() const;
	//衝突時リアクション
	virtual void onCollide(Actor& other);
	//メッセージ処理
	virtual void receiveMessage(EventMessage message, void* param);
	//衝突判定
	void collide(Actor& other);
	//ステージとの共通当たり判定
	bool field(Vector3& result);
	//ステージ床面限定当たり判定
	bool floor(Vector3& result);
	//死亡する
	void die();
	//衝突判定しているか？
	bool is_collided(const Actor& other) const;
	//死亡しているか？
	bool is_dead() const;
	//名前を取得
	const std::string& Getname() const;
	//判定の取得
	IBodyPtr GetBody()const;
	//座標を所得
	Vector3 Getposition() const;
	//回転変換行列を取得
	Matrix Getrotation() const;
	//移動速度を取得
	Vector3 Getvelocity() const;
	//変換行列を取得
	Matrix Getpose() const;

	void handleMessage(EventMessage message, void* param);

	//コピー禁止
	//Actor(const Actor& other) = delete;
	//Actor& operator=(const Actor& other) = delete;

protected:
	//ワールド
	IWorld* world_;
	//名前
	std::string name_;
	//ActorGroup group_;
	//座標
	Vector3 position_{ 0.0f,0.0f,0.0f };
	//前フレームの座標
	Vector3 prevPosition_{ Vector3::Zero };
	Matrix prevRotation_{ Matrix::Identity };
	//回転
	Matrix rotation_{ Matrix::Identity };
	//移動量
	Vector3 velocity_{ 0.0f,0.0f,0.0f };
	// 衝突判定
	IBodyPtr body_;
	//死亡フラグ
	bool dead_{ false };
	// 子アクター
	std::list<ActorPtr> children_;

	int hp_{ 0 };

};
#endif // !ACTOR_H_
