#include "ActorGroupManager.h"

//�O���[�v�̒ǉ�
void ActorGroupManager::add(ActorGroup group){
	actor_group_map_[group].clear();
}

//�A�N�^�[�̒ǉ�
void ActorGroupManager::add(ActorGroup group, const ActorPtr & actor){
	actor_group_map_[group].add(actor);
}

//�X�V
void ActorGroupManager::update(float delta_time){
	for (auto& pair : actor_group_map_) {
		pair.second.update(delta_time);
	}
}

//�`��
void ActorGroupManager::draw() const{
	for (auto& pair : actor_group_map_) {
		draw(pair.first);
	}
}

//�`��
void ActorGroupManager::draw(ActorGroup group) const{
	actor_group_map_.at(group).draw();
}

//����
void ActorGroupManager::clear(){
	actor_group_map_.clear();
}

//�A�N�^�[�̌���
ActorPtr ActorGroupManager::find(ActorGroup group, const std::string & name) const{
	return actor_group_map_.at(group).find(name);
}

//�A�N�^�[����Ԃ�
unsigned int ActorGroupManager::count(ActorGroup group) const{
	return actor_group_map_.at(group).count();
}

void ActorGroupManager::each(ActorGroup group, std::function<void(const ActorPtr&)> fn) const
{
	actor_group_map_.at(group).each(fn);
}

//�Փ˔���
void ActorGroupManager::collide(ActorGroup group1, ActorGroup group2){
	actor_group_map_[group1].collide(actor_group_map_[group2]);
}

//�폜
void ActorGroupManager::remove(){
	for (auto& pair : actor_group_map_) {
		pair.second.remove();
	}
}

//���b�Z�[�W�Ǘ�
void ActorGroupManager::handle_message(EventMessage message, void * param){
	for (auto& pair : actor_group_map_) {
		pair.second.handle_message(message, param);
	}
}
