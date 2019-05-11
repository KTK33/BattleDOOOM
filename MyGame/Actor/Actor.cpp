#include "Actor.h"
#include"../Collision/Base/HitInfo.h"

Actor::Actor() :world_(nullptr), name_("Null"), position_(Vector3::Zero), body_(std::make_shared<DummyBody>()), children_(),group_(ActorGroup::ETCETERA_ACTOR)
{
}

Actor::Actor(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body) :
	world_(world), name_(name), position_(position), body_(body), children_(), group_(ActorGroup::ETCETERA_ACTOR)
{
}

Actor::Actor(IWorld * world, const std::string & name, const Vector3 & position, const Matrix & rotation, const IBodyPtr & body) :
	world_(world), name_(name), position_(position), rotation_(rotation), body_(body), children_(), group_(ActorGroup::ETCETERA_ACTOR)
{
}

void Actor::rootInitialize()
{
	initialize();
	eachChildren([&](Actor& actor) {actor.rootInitialize(); });
}

//void Actor::rootUpdate(float deltaTime)
//{
//	//prevPosition_ = position_;
//	//prevRotation_ = rotation_;
//
//	//update(deltaTime);
//	//eachChildren([&](Actor& actor) {actor.rootUpdate(deltaTime); });
//}
//
//void Actor::rootDraw() const
//{
//	//if (isDraw_)draw();
//	//eachChildren([&](const Actor& actor) {actor.rootDraw(); });
//}
//
//void Actor::rootShadowDraw() const
//{
//	//if (isDraw_)shadowDraw();
//	//eachChildren([&](const Actor& actor) {actor.rootShadowDraw(); });
//}

void Actor::initialize()
{
	dead_ = false;
	isDraw_ = true;
}

void Actor::update(float delta_time) {}

void Actor::draw() const {}

void Actor::shadowDraw() const{}

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
	//子供にも当たり判定させる
	eachChildren([&](Actor& child) { child.collide(other); });
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
	if (CollisionMesh::collide_line(prevPosition_ + rotation_.Up()*(body_->length()*0.5f), position_ + rotation_.Up()*(body_->radius() + body_->length()*0.5f), reinterpret_cast<Vector3*>(&hitPos))){
		const Vector3 upVec = rotation_.Up()*(body_->radius() + body_->length()*0.5f);
		position_ = hitPos - upVec;
	}
	Vector3 hitcenter;
	if (CollisionMesh::collide_capsule(
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
	if (CollisionMesh::collide_line(position_, prevPosition_, reinterpret_cast<Vector3*>(&hitpos))) {
		position_ = hitpos + rotation_.Up()*(body_->radius() + body_->length()*0.5f);
	}
	if (CollisionMesh::collide_line(position_, position_ + rotation_.Down()*(body_->radius() + body_->length()*0.5f + 2.f), reinterpret_cast<Vector3*>(&hitpos))) {
		result = hitpos;
		return true;
	}
	return false;
}

void Actor::addChild(ActorPtr child)
{
	children_.push_back(child);
}

void Actor::setNumber(int cn)
{
	characterNumber_ = cn;
}

int Actor::getNumber() const
{
	return characterNumber_;
}

void Actor::setGroup(ActorGroup group)
{
	group_ = group;
}

ActorGroup Actor::getGroup() const
{
	return group_;
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

void Actor::clearChildren()
{
	children_.clear();
}

ActorPtr Actor::findCildren(const std::string & name)
{
	return findCildren(
		[&](const Actor& actor) { return actor.Getname() == name; });
}

ActorPtr Actor::findCildren(std::function<bool(const Actor&)> fn)
{
	//条件式に合った子供がいたらそれを取ってくる
	const auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorPtr& child) { return fn(*child); });
	if (i != children_.end()) {
		return *i;
	}
	//子供が更に子供を持っていた場合、その中からも捜す
	for (const auto& child : children_) {
		const auto actor = child->findCildren(fn);
		if (actor != nullptr) {
			return actor;
		}
	}
	//対象がいなかったらnullを返す
	return nullptr;
}

void Actor::findCildren(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	//子の中から名前が合ってる相手をリストに追加していく
	eachChildren([&](Actor& actor) {
		if (actor.Getname() == name) {
			//自身のshared_ptrをweak_ptrのリストに入れる
			actorList.push_back(actor.shared_from_this());
		}
	});
}

std::list<ActorPtr>& Actor::getChildren()
{
	return children_;
}

void Actor::eachChildren(std::function<void(Actor&)> fn)
{
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

void Actor::eachChildren(std::function<void(const Actor&)> fn) const
{
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

void Actor::collideChildren(Actor & other)
{
	eachChildren(
		[&](Actor& my) {
		other.eachChildren([&](Actor& target) { my.collide(target); });
	});
}

void Actor::removeChildren()
{
	//removeChildren([](Actor& child) { return child.die(); });
	//eachChildren([](Actor& child) { child.removeChildren(); });
}

void Actor::removeChildren(std::function<bool(Actor&)> fn)
{
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

void Actor::handleMessage(EventMessage message, void * param)
{
	//全員にメッセージを送る
	eachChildren([&](Actor& actor) {
		receiveMessage(message, param);
	});
}

void Actor::setDraw(bool isDraw)
{
	isDraw_ = isDraw;
}
