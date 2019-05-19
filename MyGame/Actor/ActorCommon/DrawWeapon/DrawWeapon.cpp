#include "DrawWeapon.h"
#include "../Mesh/StaticMesh.h"

void DrawWeapon::draw(int weaponNum, int weaponPos, AnimatedMesh lmesh) const
{
	StaticMesh::bind(weaponNum);
	StaticMesh::transform(lmesh.bone_matrix(weaponPos));
	StaticMesh::draw();
}
