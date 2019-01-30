#ifndef FIELD_H_
#define FIELD_H_

#include "../Math/Vector3.h"
#include "../Mesh/CollisionMesh.h"

//class Ray;
//class Line;
class BoundingSphere;

//
class Field {
public:
	//
	Field(int field = -1);
	// çXêV
	void update(float deltaTime);

	void draw() const;

	int modelHandle();
	CollisionMesh& getMesh();

	
	int getWidth()const;
	int getHeight()const;

	Field(const Field& other) = delete;
	Field& operator=(const Field& other) = delete;

private:

	int field_;

	CollisionMesh mesh_;

};
#endif // !FIELD_H_
