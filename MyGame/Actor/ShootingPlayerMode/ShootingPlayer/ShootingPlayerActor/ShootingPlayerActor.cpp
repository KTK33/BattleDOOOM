#include "ShootingPlayerActor.h"
#include "../Game/Define.h"
#include "ShootingActorStateInc.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerMotionNum.h"
#include "ShootingPlayerParam/ShootingPlayerParam.h"
#include "../Input/InputInfoInc.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Texture/Sprite.h"
#include "../Sound/Sound.h"	
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerItemBox/ShootingPlayerItemBox.h"

ShootingPlayerActor::ShootingPlayerActor(int model, int weapon, IWorld * world, const Vector3 & position, std::weak_ptr<Actor> ui, const IBodyPtr & body):
	Actor(world,"Player",position,body),
	m_ui{ ui },
	mesh_{ model,weapon },
	mweapon_{ weapon },
	mweaponPos{ 103 },
	mInitAimPos{ position_.x + rotation_.Forward().x * 10 + rotation_.Right().x * 5, position_.y + 15, position_.z + rotation_.Forward().z * 10 + rotation_.Right().z * 5 },
	mRecoverItemCount{ 1 },
	mAttackItemCount{ 1 },
	mAttackUpCheck{ false },
	mAttackUpTime{ AttackUpTime }
{
	mcurrentStateID = ActorStateID::ShootingPlayerIdle;
	shootingplayerState_[ActorStateID::ShootingPlayerIdle].add(add_state<ShootingPlayerIdle>(world, parameters_));
	shootingplayerState_[ActorStateID::ShootingPlayerAimToIdle].add(add_state<ShootingPlayerAim_Idle>(world, parameters_));
	shootingplayerState_[ActorStateID::ShootingPlayerDamage].add(add_state<ShootingPlayerDamage>(world, parameters_));
	shootingplayerState_[ActorStateID::ShootingPlayerDead].add(add_state<ShootingPlayerDead>(world, parameters_));
	shootingplayerState_[ActorStateID::ShootingPlayerGun].add(add_state<ShootingPlayerGun>(world, parameters_));
	shootingplayerState_[ActorStateID::ShootingPlayerGunPunch].add(add_state<ShootingPlayerGunPunch>(world, parameters_));
	shootingplayerState_[ActorStateID::ShootingPlayerIdleAiming].add(add_state<ShootingPlayerIdleAiming>(world, parameters_));
	shootingplayerState_[ActorStateID::ShootingPlayerIdleToAim].add(add_state<ShootingPlayerIdle_Aim>(world, parameters_));
	shootingplayerState_[ActorStateID::ShootingPlayerJump].add(add_state<ShootingPlayerJump>(world, parameters_));
	shootingplayerState_[ActorStateID::ShootingPlayerReload].add(add_state<ShootingPlayerReload>(world, parameters_));
	shootingplayerState_[ActorStateID::ShootingPlayerThohatu].add(add_state<ShootingPlayerProvocation>(world, parameters_));
	shootingplayerState_[mcurrentStateID].initialize();

	initialize();
}

void ShootingPlayerActor::initialize()
{

	rotation_ = Matrix::Identity;
	mesh_.transform(Getpose());

	parameters_.Set_Position(position_);
	parameters_.Set_HP(ShootingPlayerHPVal);
	parameters_.Set_StateID(mcurrentStateID);
	parameters_.Set_PreveStateID(mcurrentStateID);
	

	ShootingPlayerParam::getInstance().initialize();
	ActorSystem::TransparenceInit();

	mParamUI.initialize();
}

void ShootingPlayerActor::update(float deltaTime)
{

	//前フレームのポジションとして保存する
	prevPosition_ = position_;

	//壁床とのの当たり判定
	collision();

	//ポーズ中は返す
	if (world_->GetPauseCheck()) return;

	//ステイトクラスの情報を更新する
	shootingplayerState_[mcurrentStateID].update(position_, rotation_, mesh_);

	//ステイトが変わった際に呼び出される
	if (shootingplayerState_[mcurrentStateID].Get_NextStateFlag())
	{
		parameters_.Set_PreveStateID(parameters_.Get_StateID());
		shootingplayerState_[mcurrentStateID].NextState(mcurrentStateID);
		shootingplayerState_[mcurrentStateID].initialize();
		parameters_.Set_StateID(mcurrentStateID);
		parameters_.Set_Statetimer(0.0f);
	}

	//死亡状態
	if (parameters_.Get_IsDead() == true)
	{
		GameDataManager::getInstance().SetPlayerDead(true);
		return;
	}

	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(parameters_.Get_Motion());

	//パラメータをセット
	ParamSet();

	//重力
	mG.gravity(position_, velocity_, Floorcollide);

	//状態時間を加算
	parameters_.Add_Statetime(0.5f);

	//入力情報(移動)
	input_information();

	//敵の攻撃を食らったら点滅させる
	invincibly(parameters_.Get_invincibly());

	//十字キー右を押したらアイテムボックスを生成
	if(DPad::GetInstance().GetRight())
	{
		if (world_->find_actor(ActorGroup::ItemBoxUI, "PlayerBox") == NULL)
		{
			world_->add_actor(ActorGroup::ItemBoxUI, new_actor<ShootingPlayerItemBox>(world_, mRecoverItemCount, mAttackItemCount, weak_from_this()));
		}
	}

	//攻撃アップアイテムを使用したら指定時間、攻撃力が２倍になる
	if (mAttackUpCheck) {
		mAttackParam = 2;
		mAttackUpTime = max(mAttackUpTime - 1, 0);
		if (mAttackUpTime == 0)
		{
			mAttackUpTime = AttackUpTime;
			mAttackUpCheck = false;
		}
		world_->send_message(EventMessage::DAMAGEPARAM, reinterpret_cast<void*>(&mAttackParam));
	}
	else {
		mAttackParam = 1;
	}
}

void ShootingPlayerActor::draw() const
{
	mesh_.draw();
	mDW.draw(mweapon_, mweaponPos, mesh_);
	mParamUI.draw();
}

void ShootingPlayerActor::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER, reinterpret_cast<void*>(&hitdir));
}

void ShootingPlayerActor::receiveMessage(EventMessage message, void * param)
{
	//無敵でないときに敵の弾に当たったら
	if (parameters_.Get_invincibly() == false)
	{
		if (message == EventMessage::HIT_ENEMY_BULLET)
		{
			parameters_.Red_HP(*static_cast<int*>(param));
			parameters_.Set_Invicibly(true);
		}
	}

	//弾を入手したとき
	if (message == EventMessage::GET_BULLET)
	{
		int have = ShootingPlayerParam::getInstance().Get_HaveGun();
		ShootingPlayerParam::getInstance().Set_HaveGun(have + *static_cast<int*>(param));
		m_ui.lock()->receiveMessage(EventMessage::GET_BULLET, nullptr);
	}

	//回復アイテムを入手したとき
	if (message == EventMessage::GET_HPRECOVER)
	{
		mRecoverItemCount = mRecoverItemCount + 1;
		m_ui.lock()->receiveMessage(EventMessage::GET_HPRECOVER, nullptr);
	}

	//回復アイテムを使ったとき
	if (message == EventMessage::HP_RECOVER)
	{
		int nowHp = parameters_.Get_HP();
		parameters_.Set_HP(nowHp + *static_cast<int*>(param));
		mRecoverItemCount = mRecoverItemCount - 1;
	}

	//攻撃アップアイテムを使ったとき
	if (message == EventMessage::ATTACK_UP)
	{
		mAttackUpCheck = *static_cast<bool*>(param);
		m_ui.lock()->receiveMessage(EventMessage::ATTACK_UP, reinterpret_cast<bool*>(param));
		mAttackItemCount = mAttackItemCount - 1;
	}

	//的に接触したときに押しだす
	if (message == EventMessage::HIT_ENEMY)
	{
		velocity_ = mAP.Hit(*static_cast<Vector3*>(param));
	}

	//照準ポジションの取得
	if (message == EventMessage::SIGHT_POSITION)
	{
		Vector3 pos = *static_cast<Vector3*>(param);
		ShootingPlayerParam::getInstance().Set_AimPos(pos);
	}

	//カメラの向き
	if (message == EventMessage::SIGHT_ROTATION)
	{
		float rote = *(float*)param;
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), *static_cast<float*>(param));
		rotation_.NormalizeRotationMatrix();
	}
}

void ShootingPlayerActor::ParamSet()
{
	mParamUI.SetHP(parameters_.Get_HP());
	mParamUI.SetRemainGun(ShootingPlayerParam::getInstance().Get_RemainGun());
	mParamUI.SetHaveGun(ShootingPlayerParam::getInstance().Get_HaveGun());

	const Vector3 sightpos = ShootingPlayerParam::getInstance().Get_AimPos() + rotation_.Forward() * 4 + rotation_.Right() * 3;
	mParamUI.SetAimPos(sightpos, ShootingPlayerParam::getInstance().Get_AimCheck());

	//セットされている弾数が０の時に描画する
	if (ShootingPlayerParam::getInstance().Get_RemainGun() == 0) {
		mParamUI.SetGunEmpty(true);
	}
	else {
		mParamUI.SetGunEmpty(false);
	}
}

void ShootingPlayerActor::collision()
{
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		position_.x = result.x;
		position_.z = result.z;
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

void ShootingPlayerActor::input_information()
{
	//アイドル状態ならアイドルモーションに更新
	if (parameters_.Get_StateID() == ActorStateID::ShootingPlayerIdle)
{
		parameters_.Set_Motion(ShootingPlayerMotionNum::MotionPlayerIdel);
	}

	//エイム中ならエイムモーションに更新
	if (parameters_.Get_StateID() == ActorStateID::ShootingPlayerIdleAiming)
	{
		parameters_.Set_Motion(ShootingPlayerMotionNum::MotionPlayerIdleAiming);
	}

	Vector2 input;
	float yaw_speed = 0.0f;

	//上下左右入力
	mI.Input(input, yaw_speed);

	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), yaw_speed * 1.0f);
	rotation_.NormalizeRotationMatrix();

	//入力が両方０ならばアイドル状態
	if (input.x == 0.0f && input.y == 0.0f) return;

	if (parameters_.Get_StateID() == ActorStateID::ShootingPlayerIdle)
	{
		movement(1.0f, input);
	}

	if (parameters_.Get_StateID() == ActorStateID::ShootingPlayerIdleAiming)
	{
		gun_movement(0.5f, input);
	}
}

void ShootingPlayerActor::movement(float speed, Vector2 input)
{
	mMV.Move(position_, velocity_, rotation_, speed, input);

	//スティックの倒し具合でモーション変更
	if (MathHelper::Abs(input.x) < 0.75f || MathHelper::Abs(input.y) < 0.75f) {
		parameters_.Set_Motion(ShootingPlayerMotionNum::MotionPlayerWalk);
	}
	else {
		parameters_.Set_Motion(ShootingPlayerMotionNum::MotionPlayerRun);
	}
}

void ShootingPlayerActor::gun_movement(float speed, Vector2 input)
{
	mMV.Move(position_, velocity_, rotation_, speed, input);

	//スティックの倒し具合でモーション変更
	if (input.x != 0.0f){
		parameters_.Set_Motion(ShootingPlayerMotionNum::MotionPlayerLeftGun);
		return;
	}

	if (input.y != 0.0f){
		parameters_.Set_Motion(ShootingPlayerMotionNum::MotionPlayerForwardGun);
		return;
	}
}

void ShootingPlayerActor::invincibly(bool check)
{
	//モデルを点滅させる
	if (check) {
		ActorTransparence();
	}
	else{
		TransparenceInit();
	}
}