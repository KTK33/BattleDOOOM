#pragma once

#include <string>

#include "../Math/MathH.h"
#include "../Collision/Base/IBodyPtr.h"

#include "ActorState/ActorStateID.h"

//アクターパラメータ所持クラス
class ActorParameters
{
public:
	ActorParameters();

	//名前取得
	std::string Get_Name()const;
	//名前設定
	void Set_Name(std::string lname);

	//ポジション取得
	Vector3 Get_Position()const;
	//ポジション設定
	void Set_Position(Vector3 lposition);

	//移動量取得
	Vector3 Get_Velocity()const;
	//移動量設定
	void Set_Velocity(Vector3 lvelocity);

	//1フレーム前のポジション取得
	Vector3 Get_PrevPosition()const;
	//1フレーム前のポジション設定
	void Set_PrevPosition(Vector3 lprevposition);

	//回転取得
	Matrix Get_Rotation()const;
	//回転設定
	void Set_Rotation(Matrix lmatrix);

	//判定の取得
	IBodyPtr Get_Body()const;
	//判定の設定
	void Set_Body(IBodyPtr lbody);

	//死亡判定取得
	bool Get_IsDead()const;
	//死亡判定設定
	void Set_IsDead(bool lisFlag); 

	//モーションの取得
	int Get_Motion() const;
	//モーションの設定
	void Set_Motion(int num);

	//状態の取得
	ActorStateID Get_StateID()const;
	//状態の設定
	void Set_StateID(ActorStateID lstateID);

	//前状態の取得
	ActorStateID Get_PrevStateID()const;
	//前状態の設定
	void Set_PreveStateID(ActorStateID lprevstateID);

	//ステイトの時間取得
	float Get_Statetimer() const;
	//ステイトの時間設定
	void Set_Statetimer(float ltime);
	//ステイトの時間加算
	void Add_Statetime(float atime);

	//HPの取得
	int Get_HP() const;
	//HPの設定
	void Set_HP(int lhp);
	//HPの減算
	void Red_HP(int rhp);

	//無敵時間か取得
	bool Get_invincibly();
	//無敵時間かをセット
	void Set_Invicibly(bool check);

	//攻撃するかのチェック
	bool Get_Attack();
	void Set_Attack(bool at);

	//攻撃の種類
	int GetAttackType();
	void Set_AttackType(int type);

private:
	std::string mname{};

	Vector3 mposition{ Vector3::Zero };
	Vector3 mvelocity{ Vector3::Zero };
	Vector3 mprevposition{ Vector3::Zero };

	Matrix mrotation{ Matrix::Identity };

	// 衝突判定
	IBodyPtr mbody_{nullptr};

	bool misDead{ false };

	int mmotion{ 0 };

	ActorStateID mstate{ ActorStateID::NONE };
	ActorStateID mprevstate{ ActorStateID::NONE };

	float mstatetimer{ 0.0f };

	int mhp{ 0 };

	bool mInvCheck{ false };

	bool mAttack{ false };

	int mAtype{ 0 };
};