#include "ActorManager.h"

//初期化
void ActorManager::initialize()
{
}

//アクターの追加
void ActorManager::add(const ActorPtr & actor){
	actors_.push_front(actor);
}

//更新
void ActorManager::update(float delta_time){
	for (const auto& actor : actors_) {
		actor->update(delta_time);
	}
}

//描画
void ActorManager::draw() const{
	for (const auto& actor : actors_) {
		actor->draw();
	}
}

void ActorManager::shadowDraw() const
{
	root_->shadowDraw();
}

//衝突判定
void ActorManager::collide(){
	for (auto i = actors_.begin(); i != actors_.end(); ++i) {
		for (auto j = std::next(i); j != actors_.end(); ++j) {
			(*i)->collide(**j);
		}
	}
}

//衝突判定
void ActorManager::collide(Actor & other){
	for (const auto& actor : actors_) {
		other.collide(*actor);
	}
}

//衝突判定
void ActorManager::collide(ActorManager & other){
	for (const auto& actor : actors_) {
		other.collide(*actor);
	}
}

//削除
void ActorManager::remove(){
	//死んだキャラは削除する
	actors_.remove_if([](const ActorPtr& actor) {return actor->is_dead(); });
}

//アクターを見つける
ActorPtr ActorManager::find(const std::string & name) const{
	for (const auto& actor : actors_) {
		if (actor->Getname() == name) {
			return actor;
		}
	}
	return ActorPtr();
}

//アクター数を返す
unsigned int ActorManager::count() const{
	return (unsigned int)actors_.size();
}

//アクターの巡回
void ActorManager::each(std::function<void(const ActorPtr&)> fn) const
{
	for(const auto& actor : actors_)
	{
		fn(actor);
	}
}

//メッセージの送信
void ActorManager::handle_message(EventMessage message, void * param){
	for (const auto& actor : actors_) {
		actor->receiveMessage(message, param);
	}
}

//消去
void ActorManager::clear(){
	actors_.clear();
}
