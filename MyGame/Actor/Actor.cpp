#include "Actor.h"
#include"../Collision/Base/HitInfo.h"

Actor::Actor() :world_(nullptr), name_("Null"), position_(Vector3::Zero), body_(std::make_shared<DummyBody>()), children_()/*, group_(ActorGroup::ETCETERA_ACTOR)*/
{
}

Actor::Actor(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body) :
	world_(world), name_(name), position_(position), body_(body), children_()/*, group_(ActorGroup::ETCETERA_ACTOR)*/
{
}

Actor::Actor(IWorld * world, const std::string & name, const Vector3 & position, const Matrix & rotation, const IBodyPtr & body) :
	world_(world), name_(name), position_(position), rotation_(rotation), body_(body), children_()/*, group_(ActorGroup::ETCETERA_ACTOR)*/
{
}

void Actor::initialize()
{
}

void Actor::update(float delta_time){}

void Actor::draw() const{}

void Actor::onCollide(Actor & other){}

void Actor::receiveMessage(EventMessage message, void * param){}

bool Actor::is_collided(const Actor & other) const {
	//return body().intersects(other.body());
	HitInfo hitInfo;
	return body_->transform(Getpose())->isCollide(*other.GetBody()->transform(other.Getpose()).get(), hitInfo);
}

void Actor::collide(Actor & other){
	if (is_collided(other)) {
		onCollide(other);
		other.onCollide(*this);
	}
}


void Actor::die(){
	dead_ = true;
}

bool Actor::is_dead() const{
	return dead_;
}

const std::string & Actor::Getname() const{
	return name_;
}

IBodyPtr Actor::GetBody() const
{
	return body_;
}

Vector3 Actor::Getposition() const{
	return position_;
}

Matrix Actor::Getrotation() const{
	return rotation_;
}

Vector3 Actor::Getvelocity() const{
	return velocity_;
}

Matrix Actor::Getpose() const{
	//return rotation().Translation(position_);
	return Matrix(rotation_).Translation(position_);
}