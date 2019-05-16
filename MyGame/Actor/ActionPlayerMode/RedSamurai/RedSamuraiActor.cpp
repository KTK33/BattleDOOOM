#include "RedSamuraiActor.h"
#include "../Actor/PlayerBullet/PlayerBullet.h"
#include "../../ActorGroup.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"
#include "../Texture/Sprite.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Actor/Player/PlayerItemBox/PlayerItemBox.h"
#include "RedSamuraiMotionNum.h"
#include "Arrow/ArrowAttack.h"
#include "../Actor/EnemyAttackCollison/EnemyAttackCollison.h"

#include "State/RedSamuraiIdle.h"
#include "State/RedSamuraiWalk.h"
#include "State/RedSamuraiAttack.h"
#include "State/RedSamuraiDead.h"

RedSamuraiActor::RedSamuraiActor(int model, int sward, int arrow, int quiver, IWorld * world, const Vector3 & position, Matrix & rotation, std::weak_ptr<Actor> ui, const IBodyPtr & body):
Actor(world, "RedSamurai", position, body),
	Initbody{ body },
	m_ui{ ui },
	player_{ nullptr },
	mesh_{ model,sward },
	sword_{ sward },
	arrow_{ arrow },
	quiver_{ quiver },
	mSwordPos{ 38 },
	mArrowPos{ 76 },
	mQuiverPos{ 82 }
{
	rotation_ = rotation;

	mcurrentStateID = ActorStateID::RedSamuraiIdel;
	redsamuraiState_[ActorStateID::RedSamuraiIdel].add(add_state<RedSamuraiIdle>(world, parameters_));
	redsamuraiState_[ActorStateID::RedSamuraiWalk].add(add_state<RedSamuraiWaik>(world, parameters_));
	redsamuraiState_[ActorStateID::RedSamuraiAttack].add(add_state<RedSamuraiAttack>(world, parameters_));
	redsamuraiState_[ActorStateID::RedSamuraiDead].add(add_state<RedSamuraiDead>(world, parameters_));
	redsamuraiState_[mcurrentStateID].initialize();

	initialize();
}

void RedSamuraiActor::initialize()
{
	mesh_.transform(Getpose());
	velocity_ = Vector3::Zero;

	parameters_.Set_Position(position_);
	parameters_.Set_HP(PlayerHP);
}

void RedSamuraiActor::update(float deltaTime)
{
	//ステイトクラスの情報を更新する
	redsamuraiState_[mcurrentStateID].update(position_,rotation_,mesh_);

	//ステイトが変わった際に呼び出される
	if (redsamuraiState_[mcurrentStateID].Get_NextStateFlag())
	{
		redsamuraiState_[mcurrentStateID].NextState(mcurrentStateID);
		redsamuraiState_[mcurrentStateID].initialize();
		parameters_.Set_StateID(mcurrentStateID);
	}

	//壁床とのの当たり判定
	collision();

	//ポーズ中は返す
	if (world_->GetPauseCheck() == true) return;

	//死んでいる状態
	if (parameters_.Get_IsDead() == true)
	{
		GameDataManager::getInstance().SetDeadBossEnemy(true);
		return;
	}

	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(parameters_.Get_Motion());

	//ポジションの更新
	position_ = parameters_.Get_Position();

	//重力の処理
	gravity_process();

	//プレイヤーの取得
	getPlayer();

	//攻撃状態以外の時にプレイヤーの方向に向く
	if(mcurrentStateID != ActorStateID::RedSamuraiAttack) rotation_ *= PlayerLook();

	//UIのアクターにHP情報を送る
	int hp = parameters_.Get_HP();
	m_ui.lock()->receiveMessage(EventMessage::SAMURAI_HP, reinterpret_cast<void*>(&hp));

	//状態時間を加算
	parameters_.Add_Statetime(0.5f);

	//武器の位置
	weapon_transfer();
}

void RedSamuraiActor::draw() const
{
	mesh_.draw();
	draw_weapon();

	SetFontSize(32);
	DrawFormatString(1400, 450, GetColor(255, 0, 0), "%f", position_.x);
	DrawFormatString(1400, 550, GetColor(255, 0, 0), "%f", position_.y);
	DrawFormatString(1400, 650, GetColor(255, 0, 0), "%f", position_.z);
	DrawFormatString(1400, 700, GetColor(255, 0, 0), "%i", mSwordPos);
	DrawFormatString(1400, 750, GetColor(255, 0, 0), "%f", Vector3::Distance(position_, player_->Getposition()));
	SetFontSize(16);

}

void RedSamuraiActor::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_ENEMY, (int*)&hitdir);
}

void RedSamuraiActor::receiveMessage(EventMessage message, void * param)
{
	//プレイヤーの攻撃を受けた際にHPを減らす
	if (message == EventMessage::HIT_PLAYER_PUNCH)
	{
		parameters_.Red_HP(*static_cast<int*>(param));
	}

	//プレイヤーと接触したときに重ならないように押し出す
	if (message == EventMessage::HIT_PLAYER)
	{
		Hit(*(Vector3*)param);
	}
}

void RedSamuraiActor::getPlayer()
{
	//プレイヤーの取得
	player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;
}

void RedSamuraiActor::collision()
{
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		position_.x = result.x;
		position_.z = result.z;
		Stagecollide = true;
	}
	else {
		Stagecollide = false;
	}

	//床との接地判定
	if (floor(result)) {
		Floorcollide = true;
		position_ = result + rotation_.Up()*(body_->length()*0.7f + body_->radius()*0.7f);
	}
	else {
		Floorcollide = false;
	}
}

void RedSamuraiActor::gravity_process()
{
	//重力処理
	velocity_ = Vector3::Zero;
	velocity_ += Vector3::Up * -gravity;
	position_ += velocity_;

	velocity_ *= 0.8f;
	if (velocity_.Length() < 0.01f) {
		velocity_ = 0.0f;
	}
	if (Floorcollide) gravity = 0.0f;
	else gravity = 9.8f*0.1f;
}

Matrix RedSamuraiActor::PlayerLook()
{
	//ターゲット方向に少しずつ向きを変える Clampで無理やり角度(-TurnAngle～TurnAngle)内に
	const auto angle = MathHelper::Clamp(PlayerDirection(player_, position_, rotation_), -2.5f, 2.5f);
	return  Matrix::CreateRotationY(angle);
}

void RedSamuraiActor::draw_weapon() const
{
	StaticMesh::bind(sword_);
	StaticMesh::transform(mesh_.bone_matrix(mSwordPos));
	StaticMesh::draw();

	StaticMesh::bind(arrow_);
	StaticMesh::transform(mesh_.bone_matrix(mArrowPos));
	StaticMesh::draw();

	StaticMesh::bind(quiver_);
	StaticMesh::transform(mesh_.bone_matrix(mQuiverPos));
	StaticMesh::draw();
}

void RedSamuraiActor::weapon_transfer()
{
	mArrowPos = 76;
	if (world_->find_actor(ActorGroup::EnemyBullet, "ArrowAttack") == NULL)return;
	mArrowPos = 38;
}

void RedSamuraiActor::Hit(const Vector3 & dir)
{
	const Vector3 dir_ = Vector3::Normalize(dir);
	//アクターからプレイヤーの方向に移動
	velocity_ = Vector3::Up * 7.0f + Vector3{ dir_.x,0.f,dir_.z } *2.0f;
	velocity_.x = Vector3::Up.x * 7.0f + dir_.x*2.0f;
	velocity_.z = Vector3::Up.z * 7.0f + dir_.z*2.0f;
	velocity_.y = 0.0f;
	//collide = true;
}
