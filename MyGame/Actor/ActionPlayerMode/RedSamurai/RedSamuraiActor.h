#pragma once

#include "../Actor/Actor.h"
#include "../Collision/BoundingCapsule.h"
#include "../Mesh/SkeletalMesh.h"
#include "../Mesh/StaticMesh.h"
#include "../Animation/Animation.h"
#include "../Animation/AnimationMesh.h"
#include "../World/World.h"
#include "../Actor/ActorSystem/ActorSystem.h"

#include <map>
#include "../Actor/ActorState/ActorStateID.h"
#include "../Actor/ActorParameters.h"
#include "../Actor/ActorState/ActorStateManager.h"

class RedSamuraiActor : public Actor, public ActorSystem {
public:
	RedSamuraiActor(int model, int sward, int arrow, int quiver, IWorld* world, const Vector3& position, Matrix & rotation, std::weak_ptr<Actor> ui, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,9.0f,0.0f }, Matrix::Identity, 10.0f, 4.0f));
	virtual ~RedSamuraiActor() override {};

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw() const override;

	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	//�v���C���\�̌���
	void getPlayer();
	//�ǂƏ��̔���
	void collision();
	//�d�͏���
	void gravity_process();
	//�v���C���[����
	Matrix PlayerLook();
	//����̕`��
	void draw_weapon() const;
	//����̈ړ�
	void weapon_transfer();
	//�ڐG
	void Hit(const Vector3& dir);
private:
	std::weak_ptr<Actor> m_ui{};
	IBodyPtr Initbody;
	Actor* player_;
	//�A�j���[�V�������b�V��
	AnimatedMesh mesh_;
	//���������f��
	int sword_;
	int arrow_;
	int quiver_;

	//�ړ����x
	const float WalkSpeed{ 0.25f };
	//����`��ʒu
	int mSwordPos;
	int mArrowPos;
	int mQuiverPos;

	using StateMap = std::map<ActorStateID, ActorStateManager>;
	StateMap redsamuraiState_;

	ActorStateID mcurrentStateID;

	ActorParameters parameters_;
};
