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
#include "ActorGroup.h"
#include "../Mesh/CollisionMesh.h"

class IWorld;
enum class EventMessage
{
	HIT_PLAYER,
	HIT_ENEMY,
	HIT_BALL,
	HIT_BALL_HEAD,
	DEAD_ENEMY,
	DUMMY_DEAD_ENEMY,
	DEAD_DUMMY_ENEMY,
	BOSS_DEAD,
	PLAYER_HP,
	PLAYER_REMAINGUN,
	PLAYER_HAVEGUN,
	HIT_PLAYER_PUNCH,
	HIT_ENEMY_BULLET,
	GET_BULLET,
	GET_HPRECOVER,
	GETPLAYERPOS,
	SIGHT_POSITION,
	SIGHT_ROTATION,
	GETENEMYPOS,
	HP_RECOVER,
	ATTACK_UP,
	BOSSHP,
	ATTCKPARAM,
	DAMAGEPARAM,
	ACTION_CAMERA_FORWARD,
	ACTION_CAMERA_RIGHT,
};
//アクタークラス
class Actor :public std::enable_shared_from_this<Actor> {
public:
	//コンストラクタ
	Actor();
	Actor(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body = std::make_shared<DummyBody>());
	Actor(IWorld* world, const std::string& name, const Vector3& position, const Matrix& rotation, const IBodyPtr& body = std::make_shared<DummyBody>());
	//仮想デストラクタ
	virtual ~Actor(){}
	//子を初期化
	void rootInitialize();
	//子を更新
	void rootUpdate(float deltaTime);
	//子を描画
	void rootDraw() const;
	void rootShadowDraw()const;

	//初期化
	virtual void initialize();
	//更新
	virtual void update(float delta_time);
	//描画
	virtual void draw() const;
	virtual void shadowDraw() const;
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
	//子供を追加する
	void addChild(ActorPtr child);
	//識別番号の設定
	void setNumber(int cn);
	//識別番号の取得
	int getNumber()const;
	//種類の設定
	void setGroup(ActorGroup group);
	//種類の取得
	ActorGroup getGroup()const;
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

	//子を全て消す
	void clearChildren();
	//名前を基準に検索を行う
	ActorPtr findCildren(const std::string& name);
	//関数の条件に合った対象のうち一番早く見つかった物を取ってくる
	ActorPtr findCildren(std::function<bool(const Actor&)> fn);
	void findCildren(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList);

	std::list<ActorPtr>& getChildren();

	// 子を巡回
	void eachChildren(std::function<void(Actor&)>  fn);
	// 子を巡回 (const版）
	void eachChildren(std::function<void(const Actor&)> fn) const;

	void collideChildren(Actor& other);

	//子の削除
	void removeChildren();
	//子の削除
	void removeChildren(std::function<bool(Actor&)> fn);

	void handleMessage(EventMessage message, void* param);

	void setDraw(bool isDraw);

	//コピー禁止
	//Actor(const Actor& other) = delete;
	//Actor& operator=(const Actor& other) = delete;

protected:
	//キャラクター識別番号
	int characterNumber_{ -1 };
	//自身の種類
	ActorGroup group_;
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

	CollisionMesh mesh_;

	bool isDraw_{ true };

};
#endif // !ACTOR_H_
