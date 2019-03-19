#include "World.h"
#include "../Fiield/Field.h"
#include "../Actor/ActorGroup.h"
#include "../Actor/Actor.h"
World::World()
{
	initialize();
}

void World::initialize()
{
	SetDrawScreen(DX_SCREEN_BACK);
	clear();
	actors_.add(ActorGroup::Player);
	actors_.add(ActorGroup::PlayerBullet);
	actors_.add(ActorGroup::Enemy);
	actors_.add(ActorGroup::EnemyBullet);
	actors_.add(ActorGroup::Ball);
	actors_.add(ActorGroup::Item);
	actors_.add(ActorGroup::Effect);
	actors_.add(ActorGroup::System);
	actors_.add(ActorGroup::UI);
	actors_.add(ActorGroup::PauseUI);
	actors_.add(ActorGroup::ItemBoxUI);

	worldManager_.initialize();
	worldManager_.setupWorld(this);

	PauseCheck = false;
	BackTitleCheck = false;
}

void World::update(float delta_time)
{
	//field_->update(delta_time);
	actors_.update(delta_time);
	actors_.collide(ActorGroup::Player, ActorGroup::Enemy);
	actors_.collide(ActorGroup::Player, ActorGroup::EnemyBullet);
	actors_.collide(ActorGroup::Player, ActorGroup::Item);
	actors_.collide(ActorGroup::PlayerBullet, ActorGroup::Enemy);
	actors_.collide(ActorGroup::PlayerBullet, ActorGroup::EnemyHead);
	actors_.collide(ActorGroup::Player, ActorGroup::Ball);
	actors_.remove();
	//camera_->update(delta_time);
	//light_->update(delta_time);
	//gsUpdateEffect(delta_time);

	//field_->update(delta_time);
}

void World::draw() const
{
	//camera_->draw();
	//light_->draw();
	//field_->draw();
	actors_.draw();
}

void World::handle_message(EventMessage message, void * param)
{
	//ワールドのメッセージ処理
	listener_(message, param);
	//アクターのメッセージ処理
	actors_.handle_message(message, param);
	//camera_->handle_message(message, param);
	//light_->handle_message(message, param);
}

//イベントメッセージリスナーの登録
void World::add_event_message_listener(EventMessageListener listener)
{
	listener_ = listener;
}

void World::add_field(const FieldPtr & field)
{
	field_ = field;
}

void World::add_camera(const ActorPtr & camera)
{
	camera_ = camera;
}

void World::add_light(const ActorPtr & light)
{
	light_ = light;
}

void World::clear()
{
	actors_.clear();
	field_ = nullptr;
	light_ = nullptr;
	camera_ = nullptr;
	listener_ = [](EventMessage, void*) {};
}

void World::add_actor(ActorGroup group, const ActorPtr & actor)
{
	actors_.add(group, actor);
}

ActorPtr World::find_actor(ActorGroup group, const std::string & name) const
{
	return actors_.find(group, name);
}

unsigned int World::count_actor(ActorGroup group) const
{
	return actors_.count(group);
}

void World::each_actor(ActorGroup group, std::function<void(const ActorPtr&)> fn) const
{
	actors_.each(group, fn);
}

void World::send_message(EventMessage message, void * param)
{
	handle_message(message, param);
}

Field & World::field()
{
	return *field_;
}
std::shared_ptr<Field> World::getFieldOnly()
{
	return worldManager_.getField();
}

void World::SetPauseCheck(bool pc)
{
	PauseCheck = pc;
}

bool World::GetPauseCheck()
{
	return PauseCheck;
}

void World::SetBackTitleCheck(bool bt)
{
	BackTitleCheck = bt;
}

bool World::GetBackTitleCheck()
{
	return BackTitleCheck;
}
