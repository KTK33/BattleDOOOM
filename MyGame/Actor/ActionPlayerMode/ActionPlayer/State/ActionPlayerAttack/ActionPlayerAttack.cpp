#include "ActionPlayerAttack.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActionPlayerMode/ActionPlayer/ActionPlayerMotionNum.h"
#include "../Actor/PlayerAttackCollision/PlayerAttackCollision.h"
#include "../Input/InputInfoInc.h"
#include "../Sound/Sound.h"

ActionPlayerAttack::ActionPlayerAttack(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ActionPlayerAttack::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerAttack;

	parameters_->Set_Motion(ActionPlayerMotion::MotionPlayerAttack1);
	
	mAttackCount = 1;
}

void ActionPlayerAttack::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//モーションの終わる5フレーム前までに攻撃ボタンを押せば次の攻撃をする
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 10 && mAttackCount < 3)
	{
		Attack();
	}

	//攻撃の選択
	AttackOption(lposition, lrotation);

	//入力情報
	Input();

	//モーションの時間が終わったら移動状態へ
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time()-5)
	{
		mNextStateID = ActorStateID::ActionPlayerIdle;
		mNextStateFlag = true;
		return;
	}

	//HPが０になったら死亡
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::ActionPlayerDead;
		mNextStateFlag = true;
		return;
	}
}

void ActionPlayerAttack::Attack()
{
	if(ButtonB::GetInstance().StateDown())
	{
		parameters_->Set_Statetimer(0.0f);
		mAttackCount += 1;
		switch (mAttackCount) {
		case 2:
			parameters_->Set_Motion(ActionPlayerMotion::MotionPlayerAttack2); break;
		case 3:
			parameters_->Set_Motion(ActionPlayerMotion::MotionPlayerAttack3); break;
		default:break;
		}
	}
}

void ActionPlayerAttack::AttackOption(Vector3 lposition, Matrix lrotation)
{
	//攻撃コンボ回数によって当たり判定の生成タイミングを変える
	switch (mAttackCount) {
	case 1:
		if (parameters_->Get_Statetimer() == 18.0f)AttackCollision(lposition, lrotation, 5, 1, Vector3(0.0f, 13.0f, 0.0f), 2.5f, 3.5f); break;
	case 2:
		if (parameters_->Get_Statetimer() == 0.5f) AttackCollision(lposition, lrotation, 5, 2, Vector3(0.0f, 13.0f, 0.0f), 2.5f, 3.5f); break;
	case 3:
		if (parameters_->Get_Statetimer() == 0.5f) AttackCollision(lposition, lrotation, 5, 3, Vector3(0.0f, 13.0f, 0.0f), 2.5f, 3.5f); break;
	default:
		break;
	}

}

void ActionPlayerAttack::AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad)
{
	//攻撃当たり判定の生成
	auto AttackPunch = std::make_shared<PlayerAttackCollision>(world_, Vector3{ lposition + lrotation.Forward() * 10 },
		std::make_shared<BoundingCapsule>(spot, Matrix::Identity, len, rad));
	world_->add_actor(ActorGroup::PlayerBullet, AttackPunch);
	AttackPunch->SetParam(false, deadTime, attackParam);

	Sound::GetInstance().PlaySE(SE_ID::ACTION_SWARD);
}

void ActionPlayerAttack::Input()
{
	//ステップ
	if(ButtonA::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ActionPlayerAvoidance;
		mNextStateFlag = true;
		return;
	}
}
