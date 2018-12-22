#ifndef IWORLD_H_
#define IWORLD_H_

#include "../Actor/ActorPtr.h"
#include <string>
#include <functional>

enum class ActorGroup;
enum class EventMessage;
class Field;

// ワールド抽象インターフェース
class IWorld {
public:
	// 仮想デストラクタ
	virtual ~IWorld() {}
	// アクターを追加
	virtual void add_actor(ActorGroup group, const ActorPtr& actor) = 0;
	// アクターを検索
	virtual ActorPtr find_actor(ActorGroup group, const std::string& name) const = 0;
	// アクター数の取得
	virtual unsigned int count_actor(ActorGroup group) const = 0;
	// アクターの巡回
	virtual void each_actor(ActorGroup group, std::function<void(const ActorPtr&)> fn) const = 0;
	// メッセージを送信
	virtual void send_message(EventMessage message, void* param = nullptr) = 0;
	// フィールドを取得
	virtual Field& field() = 0;
};

#endif
