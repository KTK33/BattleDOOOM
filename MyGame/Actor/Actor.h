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
	GETENEMYPOS,
};
//�A�N�^�[�N���X
class Actor :public std::enable_shared_from_this<Actor> {
public:
	//�R���X�g���N�^
	Actor();
	Actor(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body = std::make_shared<DummyBody>());
	Actor(IWorld* world, const std::string& name, const Vector3& position, const Matrix& rotation, const IBodyPtr& body = std::make_shared<DummyBody>());
	//���z�f�X�g���N�^
	virtual ~Actor(){}
	//�q��������
	void rootInitialize();
	//�q���X�V
	void rootUpdate(float deltaTime);
	//�q��`��
	void rootDraw() const;
	void rootShadowDraw()const;

	//������
	virtual void initialize();
	//�X�V
	virtual void update(float delta_time);
	//�`��
	virtual void draw() const;
	virtual void shadowDraw() const;
	//�Փˎ����A�N�V����
	virtual void onCollide(Actor& other);
	//���b�Z�[�W����
	virtual void receiveMessage(EventMessage message, void* param);
	//�Փ˔���
	void collide(Actor& other);
	//�X�e�[�W�Ƃ̋��ʓ����蔻��
	bool field(Vector3& result);
	//�X�e�[�W���ʌ��蓖���蔻��
	bool floor(Vector3& result);
	//�q����ǉ�����
	void addChild(ActorPtr child);
	//���ʔԍ��̐ݒ�
	void setNumber(int cn);
	//���ʔԍ��̎擾
	int getNumber()const;
	//��ނ̐ݒ�
	void setGroup(ActorGroup group);
	//��ނ̎擾
	ActorGroup getGroup()const;
	//���S����
	void die();
	//�Փ˔��肵�Ă��邩�H
	bool is_collided(const Actor& other) const;
	//���S���Ă��邩�H
	bool is_dead() const;
	//���O���擾
	const std::string& Getname() const;
	//����̎擾
	IBodyPtr GetBody()const;
	//���W������
	Vector3 Getposition() const;
	//��]�ϊ��s����擾
	Matrix Getrotation() const;
	//�ړ����x���擾
	Vector3 Getvelocity() const;
	//�ϊ��s����擾
	Matrix Getpose() const;

	//�q��S�ď���
	void clearChildren();
	//���O����Ɍ������s��
	ActorPtr findCildren(const std::string& name);
	//�֐��̏����ɍ������Ώۂ̂�����ԑ�������������������Ă���
	ActorPtr findCildren(std::function<bool(const Actor&)> fn);
	void findCildren(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList);

	std::list<ActorPtr>& getChildren();

	// �q������
	void eachChildren(std::function<void(Actor&)>  fn);
	// �q������ (const�Łj
	void eachChildren(std::function<void(const Actor&)> fn) const;

	void collideChildren(Actor& other);

	//�q�̍폜
	void removeChildren();
	//�q�̍폜
	void removeChildren(std::function<bool(Actor&)> fn);

	void handleMessage(EventMessage message, void* param);

	void setDraw(bool isDraw);

	//�R�s�[�֎~
	//Actor(const Actor& other) = delete;
	//Actor& operator=(const Actor& other) = delete;

protected:
	//�L�����N�^�[���ʔԍ�
	int characterNumber_{ -1 };
	//���g�̎��
	ActorGroup group_;
	//���[���h
	IWorld* world_;
	//���O
	std::string name_;
	//ActorGroup group_;
	//���W
	Vector3 position_{ 0.0f,0.0f,0.0f };
	//�O�t���[���̍��W
	Vector3 prevPosition_{ Vector3::Zero };
	Matrix prevRotation_{ Matrix::Identity };
	//��]
	Matrix rotation_{ Matrix::Identity };
	//�ړ���
	Vector3 velocity_{ 0.0f,0.0f,0.0f };
	// �Փ˔���
	IBodyPtr body_;
	//���S�t���O
	bool dead_{ false };
	// �q�A�N�^�[
	std::list<ActorPtr> children_;

	int hp_{ 0 };

	CollisionMesh mesh_;

	bool isDraw_{ true };

};
#endif // !ACTOR_H_
