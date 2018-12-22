#include "AnimationMesh.h"

AnimatedMesh::AnimatedMesh(int mesh, int motion) :
	mesh_{ mesh },
	animation_{ mesh,motion } {}

void AnimatedMesh::update(float deltaTime)
{
	animation_.update(deltaTime);
}

void AnimatedMesh::draw() const
{
	SkeletalMesh::bind(mesh_);
	SkeletalMesh::set_world_matrices(world_matrices_.data());
	SkeletalMesh::draw();
}

void AnimatedMesh::change_motion(int motion)
{
	animation_.change_motion(motion);
}

void AnimatedMesh::transform(const Matrix& world)
{
	SkeletalMesh::bind(mesh_);
	SkeletalMesh::set_local_matrices(animation_.local_matrices().data());
	SkeletalMesh::transform(world);
	SkeletalMesh::get_world_matrices(world_matrices_.data());
}

const Matrix & AnimatedMesh::bone_matrix(int no) const
{
	return world_matrices_[no];
}

float AnimatedMesh::motion_end_time() const
{
	return animation_.end_time();
}