#ifndef FIELD_H_
#define FIELD_H_

#include "../Math/Vector3.h"

//class Ray;
//class Line;
class BoundingSphere;

//
class Field {
public:
	//
	Field(int skybox);
	//
	//bool collision(const Ray& ray, Vector3* intersect = nullptr, Plane* plane = nullptr) const;
	//
	//bool collision(const Line& line, Vector3* intersect = nullptr, Plane* plane = nullptr) const;
	//
	bool collision(const BoundingSphere& sphere, Vector3* intersect = nullptr)const;
	//
	void draw() const;
	//
	Field(const Field& other) = delete;
	Field& operator=(const Field& other) = delete;

private:
	//
	//int  octree_;
	//
	int  skybox_;
};
#endif // !FIELD_H_
