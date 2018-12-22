#include "Field.h"
#include "../Collision/BoundingSphere.h"

Field::Field(int skybox) :
	skybox_{ skybox } {
}


bool Field::collision(const BoundingSphere & sphere, Vector3 * intersect) const
{
	return TRUE;
}

void Field::draw() const
{
	//gsDrawSkyBox(skybox_);
	//gsDrawOctree(octree_);
}
