#include "ActorManager.h"

//������
void ActorManager::initialize()
{
}

//�A�N�^�[�̒ǉ�
void ActorManager::add(const ActorPtr & actor){
	actors_.push_front(actor);
}

//�X�V
void ActorManager::update(float delta_time){
	for (const auto& actor : actors_) {
		actor->update(delta_time);
	}
}

//�`��
void ActorManager::draw() const{
	for (const auto& actor : actors_) {
		actor->draw();
	}
}

void ActorManager::shadowDraw() const
{
	root_->shadowDraw();
}

//�Փ˔���
void ActorManager::collide(){
	for (auto i = actors_.begin(); i != actors_.end(); ++i) {
		for (auto j = std::next(i); j != actors_.end(); ++j) {
			(*i)->collide(**j);
		}
	}
}

//�Փ˔���
void ActorManager::collide(Actor & other){
	for (const auto& actor : actors_) {
		other.collide(*actor);
	}
}

//�Փ˔���
void ActorManager::collide(ActorManager & other){
	for (const auto& actor : actors_) {
		other.collide(*actor);
	}
}

//�폜
void ActorManager::remove(){
	//���񂾃L�����͍폜����
	actors_.remove_if([](const ActorPtr& actor) {return actor->is_dead(); });
}

//�A�N�^�[��������
ActorPtr ActorManager::find(const std::string & name) const{
	for (const auto& actor : actors_) {
		if (actor->Getname() == name) {
			return actor;
		}
	}
	return ActorPtr();
}

//�A�N�^�[����Ԃ�
unsigned int ActorManager::count() const{
	return (unsigned int)actors_.size();
}

//�A�N�^�[�̏���
void ActorManager::each(std::function<void(const ActorPtr&)> fn) const
{
	for(const auto& actor : actors_)
	{
		fn(actor);
	}
}

//���b�Z�[�W�̑��M
void ActorManager::handle_message(EventMessage message, void * param){
	for (const auto& actor : actors_) {
		actor->receiveMessage(message, param);
	}
}

//����
void ActorManager::clear(){
	actors_.clear();
}
