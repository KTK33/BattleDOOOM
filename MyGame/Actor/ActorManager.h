#ifndef ACTOR_MANAGER_H_
#define ACTOR_MANAGER_H_

#include "Actor.h"
#include "ActorPtr.h"
#include <list>
#include <functional>

enum class EventMessage;

//�A�N�^�[�}�l�[�W���[
class ActorManager {
public:
	//�R���X�g���N�^
	ActorManager() = default;

	//������
	void initialize();
	//�A�N�^�[�̒ǉ�
	void add(const ActorPtr& actor);
	//�X�V
	void update(float delta_time);
	//�`��
	void draw() const;
	void shadowDraw()const;
	//�Փ˔���
	void collide();
	//�Փ˔���
	void collide(Actor& other);
	//�Փ˔���
	void collide(ActorManager& other);
	//�폜
	void remove();
	//�A�N�^�[�̌���
	ActorPtr find(const std::string& name) const;
	//�A�N�^�[����Ԃ�
	unsigned int count() const;
	//�A�N�^�[�̏���
	void each(std::function<void(const ActorPtr&)> fn) const;
	//���b�Z�[�W����
	void handle_message(EventMessage  message, void* param);
	//����
	void clear();
	//�R�s�[�֎~
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;

private:
	using ActorList = std::list<ActorPtr>;
	//�A�N�^�[���X�g
	ActorList actors_;

	ActorPtr root_{ nullptr };
};
#endif // !ACTOR_MANAGER_H_
