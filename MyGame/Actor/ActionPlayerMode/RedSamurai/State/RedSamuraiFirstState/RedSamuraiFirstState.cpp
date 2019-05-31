#include "RedSamuraiFirstState.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActorGroup.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"
#include "../../RedSamuraiParam/RedSamuraiParam.h"
#include "../Sound/Sound.h"

RedSamuraiFirstState::RedSamuraiFirstState(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
	mmotionNum = 0;
}

void RedSamuraiFirstState::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraNoSwardIdle;

	parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiNoSwardIdle);
}

void RedSamuraiFirstState::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//プレイヤーの検索
	auto player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	//プレイヤーとの距離
	const float PlayerDis = Vector3::Distance(lposition, player_->Getposition());

	//距離が200以下なら戦闘体制に
	if (PlayerDis <= 100.0f)
	{
		if (mmotionNum == 0)
		{
			parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiSwardDraw1);
			parameters_->Set_Statetimer(0.0f);
			mmotionNum++;
		}
	}

	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		if (mmotionNum == 1)
		{
			parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiSwardDraw2);
			parameters_->Set_Statetimer(0.0f);
			mmotionNum++;
			RedSamuraiParam::getInstance().SetSwardPosNum(38);
			RedSamuraiParam::getInstance().SetSwardModelNum(11);
			Sound::GetInstance().PlaySE(SE_ID::RED_START);
		}
		else if (mmotionNum == 2)
		{
			mNextStateID = ActorStateID::RedSamuraiIdle;
			mNextStateFlag = true;
			return;
		}
	}
}
