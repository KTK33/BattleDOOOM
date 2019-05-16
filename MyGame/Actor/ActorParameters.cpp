#include "ActorParameters.h"

ActorParameters::ActorParameters()
{
}

std::string ActorParameters::Get_Name() const
{
	return mname;
}

void ActorParameters::Set_Name(std::string lname)
{
	mname = lname;
}

Vector3 ActorParameters::Get_Position() const
{
	return mposition;
}

void ActorParameters::Set_Position(Vector3 lposition)
{
	mposition = lposition;
}

Vector3 ActorParameters::Get_Velocity() const
{
	return mvelocity;
}

void ActorParameters::Set_Velocity(Vector3 lvelocity)
{
	mvelocity = lvelocity;
}

Vector3 ActorParameters::Get_PrevPosition() const
{
	return mprevposition;
}

void ActorParameters::Set_PrevPosition(Vector3 lprevposition)
{
	mprevposition = lprevposition;
}

Matrix ActorParameters::Get_Rotation() const
{
	return mrotation;
}

void ActorParameters::Set_Rotation(Matrix lmatrix)
{
	mrotation = lmatrix;
}

IBodyPtr ActorParameters::Get_Body() const
{
	return mbody_;
}

void ActorParameters::Set_Body(IBodyPtr lbody)
{
	mbody_ = lbody;
}

bool ActorParameters::Get_IsDead() const
{
	return misDead;
}

void ActorParameters::Set_IsDead(bool lisFlag)
{
	misDead = lisFlag;
}

int ActorParameters::Get_Motion() const
{
	return mmotion;
}

void ActorParameters::Set_Motion(int num)
{
	mmotion = num;
}

ActorStateID ActorParameters::Get_StateID() const
{
	return mstate;
}

void ActorParameters::Set_StateID(ActorStateID lstateID)
{
	mstate = lstateID;
}

ActorStateID ActorParameters::Get_PrevStateID() const
{
	return mprevstate;
}

void ActorParameters::Set_PreveStateID(ActorStateID lprevstateID)
{
	mprevstate = lprevstateID;
}

float ActorParameters::Get_Statetimer() const
{
	return mstatetimer;
}

void ActorParameters::Set_Statetimer(float ltime)
{
	mstatetimer = ltime;
}

void ActorParameters::Add_Statetime(float atime)
{
	mstatetimer += atime;
}

int ActorParameters::Get_HP() const
{
	return mhp;
}

void ActorParameters::Set_HP(int lhp)
{
	mhp = lhp;
}

void ActorParameters::Red_HP(int rhp)
{
	mhp -= rhp;
}