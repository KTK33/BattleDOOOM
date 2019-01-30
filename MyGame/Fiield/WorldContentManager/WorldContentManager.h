#pragma once

#include "../Field.h"
#include "../../Skybox/Skybox.h"

#include "../../Actor/ActorPtr.h"
#include "../../Actor/ActorGroup.h"
#include "../../Actor/Actor.h"
#include <list>
#include<memory>


class IWorld;

class WorldContentManager 
{

public:
	WorldContentManager();
	void initialize();
	void setupWorld(IWorld* world);
	void update(float deltaTime);
	void drawSkyBox()const;
	void draw() const;
	void actorDraw() const;
	void buildingDraw() const;
	void shadowDraw()const;

	std::shared_ptr<Field> getField();
	std::shared_ptr<Skybox> getSkybox();

	void addActor(ActorGroup group, const ActorPtr& actor);
	void addBuilding();

	ActorPtr findActor(const std::string& name);
	void findActor(ActorGroup group, const std::string& name, std::list<std::weak_ptr<Actor>>& actorList);
	void handleMessage(EventMessage message, void* param);
	unsigned int getSize(ActorGroup group) const;

	bool hitToLine(Vector3 firstPos, Vector3 secondPos);
private:

	IWorld* world_;

	std::shared_ptr<Field> field_;
	std::shared_ptr<Skybox> skybox_;
};