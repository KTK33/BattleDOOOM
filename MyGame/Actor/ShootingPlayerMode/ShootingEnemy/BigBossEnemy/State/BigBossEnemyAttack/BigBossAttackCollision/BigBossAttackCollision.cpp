#include "BigBossAttackCollision.h"

BigBossAttackCollision::BigBossAttackCollision(IWorld * world, const Vector3 & position, const Matrix & rotation, const IBodyPtr & body):
	Actor(world,"BigBossAttackActor",position,body),
	mdeadCheck{ false },
	mdeadTime{ 0 },
	mattackparam{ 0 },
	mattacktype{ 0 },
	mattacktime{ 0 }
{
	rotation_ = rotation;
}

void BigBossAttackCollision::SetParam(bool deadCheck, int deadTime, int attackParam, int attacktype)
{
	mdeadCheck = deadCheck;
	mdeadTime = deadTime;
	mattackparam = attackParam;
	mattacktype = attacktype;
}

void BigBossAttackCollision::update(float deltaTime)
{
	if (mdeadCheck) return;
	mdeadTime = max(mdeadTime - 1, 0);

	if (mdeadTime <= 0)
	{
		die();
	}

	AttackType(mattacktype);
}

void BigBossAttackCollision::draw() const
{
	body_->transform(Getpose())->draw();
}

void BigBossAttackCollision::onCollide(Actor & other)
{
	const Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY_BULLET, (void*)&mattackparam);
}

void BigBossAttackCollision::receiveMessage(EventMessage message, void * param)
{
}

void BigBossAttackCollision::AttackType(int type)
{
	//呼ばれた攻撃のタイプにより攻撃を変更
	mattacktime++;
	switch (type)
	{
	case 1:
		mCM.Move1(position_, rotation_, mattacktime);
		break;
	case 2:
		mCM.Move2(position_, rotation_, mattacktime);
		break;
	case 3:
		mCM.Move3(position_, rotation_, mattacktime);
		break;
	case 4:
		mCM.Move4(position_, rotation_, mattacktime);
		break;
	default:
		break;
	}
}
