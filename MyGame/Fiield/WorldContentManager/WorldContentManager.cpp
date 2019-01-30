 #include "WorldContentManager.h"
#include "../../World/IWorld.h"


WorldContentManager::WorldContentManager():
	skybox_(nullptr), field_(nullptr)
{
}

void WorldContentManager::initialize()
{
	
}

void WorldContentManager::setupWorld(IWorld* world)
{
	world_ = world;

	field_ = std::make_shared<Field>(0);

	//skybox_ = std::make_shared<Skybox>(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SKYBOX));
	addBuilding();
}

void WorldContentManager::update(float deltaTime)
{
	//if (field_ != nullptr) field_->update(deltaTime);
	//if (skybox_ != nullptr) skybox_->update(deltaTime);
}

void WorldContentManager::drawSkyBox() const
{
	if (skybox_ != nullptr) skybox_->draw();
	if (field_ != nullptr) field_->draw();
}

void WorldContentManager::draw() const
{
	if (skybox_ != nullptr) skybox_->draw();
	if (field_ != nullptr) field_->draw();
}

void WorldContentManager::actorDraw() const
{
}

void WorldContentManager::buildingDraw() const
{
}

void WorldContentManager::shadowDraw() const
{

}

std::shared_ptr<Field> WorldContentManager::getField()
{
	return field_;
}

std::shared_ptr<Skybox> WorldContentManager::getSkybox()
{
	return skybox_;
}

void WorldContentManager::addActor(ActorGroup group, const ActorPtr& actor)
{
}

void WorldContentManager::addBuilding()
{
	//objManager_->addBuilding(new_building<House_1>(world_,Vector3{ 150.0f, 0.0f, 0.0f }, 0));
	//objManager_->addBuilding(new_building<SmokingArea>(world_, Vector3{ -150.0f, 0.0f, 0.0f }, 0));
	//objManager_->addBuilding(new_building<Apartment_1>(world_, 4, 0, 0));
}

ActorPtr WorldContentManager::findActor(const std::string & name)
{
	return 0;
}

void WorldContentManager::findActor(ActorGroup group, const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
}

void WorldContentManager::handleMessage(EventMessage message, void * param)
{
}

unsigned int WorldContentManager::getSize(ActorGroup group) const
{
	return 0;
}

bool WorldContentManager::hitToLine(Vector3 firstPos, Vector3 secondPos)
{
	return 0;
}

