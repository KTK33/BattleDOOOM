#include "ActionPlayerActor.h"
#include "ActionStateInc.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Actor/ActionPlayerMode/UI/SceneUI/PlayerDeadUI.h"
#include "../Game/GameData/ActionMode/ActionPlayerData.h"

ActionPlayerActor::ActionPlayerActor(int model, int weapon, IWorld * world, const Vector3 & position, const Matrix& rotation,const IBodyPtr & body):
	Actor(world, "Player", position, rotation,body),
	mesh_{ model,weapon },
	mweapon_{ weapon },
	mRightweaponPos{ 15 },
	mLeftweaponPos{ 38 },
	m_ActionCameraForward{ Vector3::Zero },
	m_ActionCameraRight{ Vector3::Zero },
	mDeadArelady{ false },
	mDeadTime{ 40.0f}
{
	mcurrentStateID = ActorStateID::ActionPlayerIdle;
	actionplayerState_[ActorStateID::ActionPlayerIdle].add(add_state<ActionPlayerIdle>(world, parameters_));
	actionplayerState_[ActorStateID::ActionPlayerAttack].add(add_state<ActionPlayerAttack>(world, parameters_));
	actionplayerState_[ActorStateID::ActionPlayerAvoidance].add(add_state<ActionPlayerAvoidance>(world, parameters_));
	actionplayerState_[ActorStateID::ActionPlayerAvoidanceAttack].add(add_state<ActionPlayerAvoidanceAttack>(world, parameters_));
	actionplayerState_[ActorStateID::ActionPlayerDead].add(add_state<ActionPlayerDead>(world, parameters_));
	actionplayerState_[mcurrentStateID].initialize();

	initialize();
}

void ActionPlayerActor::initialize()
{
	mesh_.transform(Getpose());
	velocity_ = Vector3::Zero;

	parameters_.Set_Position(position_);
	parameters_.Set_HP(ActionPlayerHPVal);

	parameters_.Set_StateID(mcurrentStateID);
}

void ActionPlayerActor::update(float deltaTime)
{

	prevPosition_ = position_;

	//壁床とのの当たり判定
	collision();

	world_->send_message(EventMessage::ACTIONPLAYER_STATE, (ActorStateID*)&mcurrentStateID);

	//ポーズ中は返す
	if (world_->GetPauseCheck()) return;

	//ステイトクラスの情報を更新する
	actionplayerState_[mcurrentStateID].update(position_, rotation_, mesh_);

	//ステイトが変わった際に呼び出される
	if (actionplayerState_[mcurrentStateID].Get_NextStateFlag())
	{
		actionplayerState_[mcurrentStateID].NextState(mcurrentStateID);
		actionplayerState_[mcurrentStateID].initialize();
		parameters_.Set_StateID(mcurrentStateID);
		parameters_.Set_Statetimer(0.0f);
	}

	//死亡状態
	if (parameters_.Get_IsDead())
	{
		//死亡時の描画アクター生成
		if (!mDeadArelady) {
			world_->add_actor(ActorGroup::UI, new_actor<PlayerDeadUI>(world_));
			mDeadArelady = true;
		}
		mDeadTime -= deltaTime;
		return;
	}

	mesh_.update(deltaTime);
	mesh_.transform(Getpose());
	mesh_.change_motion(parameters_.Get_Motion());

	//重力
	mG.gravity(position_, velocity_, Floorcollide);

	//状態時間を加算
	parameters_.Add_Statetime(0.5f);

	//ボスが死んでいたら移動させない
	if (GameDataManager::getInstance().GetDeadBossEnemy()) return;

	//移動入力の情報
	if (parameters_.Get_StateID() == ActorStateID::ActionPlayerIdle || 
		parameters_.Get_StateID() == ActorStateID::ActionPlayerAvoidance)
	{
		input_information();
	}
}

void ActionPlayerActor::draw() const
{
	if (mDeadTime <= 0) return;

	mesh_.draw();
	mDW.draw(mweapon_, mRightweaponPos, mesh_);
	mDW.draw(mweapon_, mLeftweaponPos, mesh_);

	mHP.draw(parameters_.Get_HP());
}

void ActionPlayerActor::onCollide(Actor & other)
{
	Vector3 hitdir(other.Getposition() - position_);
	other.receiveMessage(EventMessage::HIT_PLAYER, reinterpret_cast<void*>(&hitdir));
}

void ActionPlayerActor::receiveMessage(EventMessage message, void * param)
{
	//敵の攻撃を受けた際にHPを減らす
	if (message == EventMessage::HIT_ENEMY_BULLET)
	{
		parameters_.Red_HP(*static_cast<int*>(param));
	}

	//敵と接触したときに重ならないように押し出す
	if (message == EventMessage::HIT_ENEMY)
	{
		velocity_ = mAP.Hit(*static_cast<Vector3*>(param));
	}

	//カメラの前方向を取得
	if (message == EventMessage::ACTION_CAMERA_FORWARD)
	{
		m_ActionCameraForward = *static_cast<Vector3*>(param);
	}

	//カメラの右方向を取得
	if (message == EventMessage::ACTION_CAMERA_RIGHT)
	{
		m_ActionCameraRight = *static_cast<Vector3*>(param);
	}
}

void ActionPlayerActor::collision()
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

void ActionPlayerActor::gravity_process()
{
	//重力処理
	//velocity_ = Vector3::Zero;
	velocity_ += Vector3::Up * -gravity;
	position_ += velocity_;

	velocity_ *= 0.8f;
	if (velocity_.Length() < 0.01f) {
		velocity_ = 0.0f;
	}
	if (Floorcollide) gravity = 0.0f;
	else gravity = 9.8f*0.1f;
}

void ActionPlayerActor::input_information()
{
	//アイドル状態ならアイドルモーションに更新
	if (parameters_.Get_StateID() == ActorStateID::ActionPlayerIdle) 
	{
		parameters_.Set_Motion(ActionPlayerMotion::MotionPlayerIdle);
	}

	Vector2 input;

	//左右上下入力
	mI.Input(input);
	//入力が両方０ならばアイドル状態
	if (input.x == 0.0f && input.y == 0.0f) return; 
	movement(ActionPlayerSpeedVal, input);
}

void ActionPlayerActor::movement(float speed, Vector2 input)
{
	//前後左右移動
	velocity_ = Vector3::Zero;
	float forward_speed = 0.0f;
	float side_speed = 0.0f;

	//入力情報を移動量に加算
	side_speed = input.x * speed;
	forward_speed = input.y * speed;

	//カメラの前方方向を前方向とする
	velocity_ += m_ActionCameraForward * forward_speed;
	velocity_ += m_ActionCameraRight * side_speed;

	//走りでの加速
	float DashSpped = 0.0f;

	//回避状態なら
	if (parameters_.Get_StateID() == ActorStateID::ActionPlayerAvoidance)
	{
		velocity_.y = 0.0f;
		velocity_ += velocity_ * mAvoidanceSpeed;
	}
	else
	{
		//スティックの倒し具合でモーション変更
		if (MathHelper::Abs(input.x) < WalkRunVal || MathHelper::Abs(input.y) < WalkRunVal) {
			parameters_.Set_Motion(ActionPlayerMotion::MotionPlayerWalk);
		}
		else {
			parameters_.Set_Motion(ActionPlayerMotion::MotionPlayerRun);
			DashSpped = ActionPlayerRunSpeedVal;
		}
	}

	//進んでいる方向に向く
	Vector3 angle = m_ActionCameraForward * input.y + m_ActionCameraRight * input.x;
	angle.y = 0.0f;
	Matrix to_Target_rotate = Matrix::CreateLookAt(position_, position_ + angle.Normalize(), Vector3::Up);
	rotation_ = Matrix::Lerp(rotation_, Matrix::Invert(to_Target_rotate) * Matrix::CreateRotationY(180), 0.3f);

	position_ += velocity_ * (1.0f + DashSpped);

	position_ = Vector3::Clamp(position_, Vector3(-278.0f, 0, -196.0f), Vector3(295.0f, 100.0f, 210.0f));
}