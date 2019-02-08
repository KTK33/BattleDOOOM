#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "../Actor/ActorGroupManager.h"
#include "../Actor/ActorPtr.h"
#include "../Fiield/FieldPtr.h"
#include "../Fiield/WorldContentManager/WorldContentManager.h"
#include <functional>

#include "../Input/GamePad.h"

enum class EventMessage;

//ワールドクラス
class World : public IWorld {
public:
	//イベントメッセージリスナー
	using EventMessageListener = std::function<void(EventMessage, void*)>;
public:
	//コンストラクタ
	World();
	//初期化
	void initialize();
	//更新
	void update(float delta_time);
	//描画
	void draw() const;
	//メッセージ処理
	void handle_message(EventMessage message, void* param);
	//メッセージリスナー登録
	void add_event_message_listener(EventMessageListener listener);
	//フィールドの追加
	void add_field(const FieldPtr& field);
	//カメラの追加
	void add_camera(const ActorPtr& camera);
	//ライトの追加
	void add_light(const ActorPtr& light);
	//消去
	void clear();

	//アクターの追加
	virtual void add_actor(ActorGroup group, const ActorPtr& actor) override;
	//アクターの検索
	virtual ActorPtr find_actor(ActorGroup group, const std::string& name)const override;
	//アクター数の取得
	virtual unsigned int count_actor(ActorGroup group) const override;
	//アクターの巡回
	virtual void each_actor(ActorGroup group, std::function<void(const ActorPtr&)>fn)const override;
	//メッセージ送信
	virtual void send_message(EventMessage message, void* param = nullptr)override;
	//
	virtual Field& field() override;
	virtual std::shared_ptr<Field> getFieldOnly() override;


	//
	World(const World& other) = delete;
	World& operator=(const World& other) = delete;

private:
	//
	ActorGroupManager    actors_;
	//
	ActorPtr             light_;
	//
	ActorPtr             camera_;
	//
	FieldPtr             field_;

	WorldContentManager worldManager_{};

	EventMessageListener listener_{ [](EventMessage,void*) {} };
};

#endif // !WORLD_H_
