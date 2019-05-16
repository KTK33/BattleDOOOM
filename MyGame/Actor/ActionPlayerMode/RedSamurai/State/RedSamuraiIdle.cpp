#include "RedSamuraiIdle.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"

RedSamuraiIdle::RedSamuraiIdle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void RedSamuraiIdle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraiIdel;
	parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiIdel);
}

void RedSamuraiIdle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ƒvƒŒƒCƒ„[‚ÌŒŸõ
	auto player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	//ˆê’è‹——£“à‚É—ˆ‚½‚çˆÚ“®ó‘Ô‚Ö
	if (Vector3::Distance(player_->Getposition(), lposition) <= 250.0f)
	{
		mNextStateID = ActorStateID::RedSamuraiWalk;
		mNextStateFlag = true;
		return;
	}

	//HP‚ª‚O‚É‚È‚Á‚½‚çŽ€–S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::RedSamuraiDead;
		mNextStateFlag = true;
		return;
	}
}
