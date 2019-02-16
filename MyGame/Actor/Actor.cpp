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

void Actor::update(float delta_time) {}

void Actor::draw() const {}

void Actor::onCollide(Actor & other) {}

void Actor::receiveMessage(EventMessage message, void * param) {}

bool Actor::is_collided(const Actor & other) const {
	//return body().intersects(other.body());
	HitInfo hitInfo;
	return body_->transform(Getpose())->isCollide(*other.GetBody()->transform(other.Getpose()).get(), hitInfo);
}

void Actor::collide(Actor & other) {
	if (is_collided(other)) {
		onCollide(other);
		other.onCollide(*this);
	}
}

//ステージとの共通当たり判定
bool Actor::field(Vector3 & result)
{
	//Vector3 hitPos;
	//if (world_->getFieldOnly()->getMesh().collide_line(prevPosition_ + rotation_.Up()*(body_->length()*0.5f), position_ + rotation_.Up()*(body_->radius() + body_->length()*0.5f), (Vector3*)&hitPos))
	//{
	//	Vector3 upVec = rotation_.Up()*(body_->radius() + body_->length()*0.5f);
	//	position_ = hitPos - upVec;
	//}
	//Vector3 hitcenter;
	//if (world_->getFieldOnly()->getMesh().collide_capsule(
	//	position_ + 
	//	rotation_.Up()*(body_->length()*0.5f),
	//	position_ + rotation_.Down()*(body_->length()*0.5f),
	//	body_->radius(), 
	//	(Vector3*)&hitcenter))
	//{
	//	result = hitcenter;

	//	return true;
	//}
	//return false;

	Vector3 hitPos;
	if (world_->field().getMesh().collide_line(prevPosition_ + rotation_.Up()*(body_->length()*0.5f), position_ + rotation_.Up()*(body_->radius() + body_->length()*0.5f), (Vector3*)&hitPos)){
		Vector3 upVec = rotation_.Up()*(body_->radius() + body_->length()*0.5f);
		position_ = hitPos - upVec;
	}
	Vector3 hitcenter;
	if (world_->getFieldOnly()->getMesh().collide_capsule(
		position_ + 
		rotation_.Up()*(body_->length()*0.5f),
		position_ + rotation_.Down()*(body_->length()*0.5f),
		body_->radius(), 
		(Vector3*)&hitcenter))
	{
		result = hitcenter;

		return true;
	}
	return false;


}

//ステージ床面限定当たり判定
bool Actor::floor(Vector3 & result)
{
	Vector3 hitpos;
	if (world_->getFieldOnly()->getMesh().collide_line(position_, prevPosition_, (Vector3*)&hitpos)) {
		position_ = hitpos + rotation_.Up()*(body_->radius() + body_->length()*0.5f);
	}
	if (world_->getFieldOnly()->getMesh().collide_line(position_, position_ + rotation_.Down()*(body_->radius() + body_->length()*0.5f + 2.f), (Vector3*)&hitpos)) {
		result = hitpos;
		return true;
	}
	return false;
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
