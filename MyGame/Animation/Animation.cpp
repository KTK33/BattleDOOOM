#include "Animation.h"

Animation::Animation(int model, int motion) :
	model_{ model },
	motion_{ motion }
{
	SkeletalMesh::bind(model_);
	SkeletalMesh::bind_animation(motion_, motion_timer_);
	SkeletalMesh::get_local_matrices(local_matrices_.data());
}

void Animation::update(float  delta_time)
{
	SkeletalMesh::bind(model_);
	SkeletalMesh::bind_animation(prev_motion_, prev_motion_timer_, motion_, motion_timer_, lerp_timer_ / LerpTime);
	SkeletalMesh::set_local_matrices(local_matrices_.data());
	motion_timer_ = std::fmod(motion_timer_ + 0.5f * delta_time, end_time());
	lerp_timer_ = std::fmin(lerp_timer_ + delta_time, LerpTime);
}

void Animation::change_motion(int motion)
{
	//åªç›Ç∆ìØÇ∂ÉÇÅ[ÉVÉáÉìÇÃèÍçáÇÕâΩÇ‡ÇµÇ»Ç¢
	if (motion == motion_) return;
	prev_motion_ = motion_;
	prev_motion_timer_ = motion_timer_;
	motion_ = motion;
	motion_timer_ = 0.0f;
	lerp_timer_ = 0.0f;
}

int Animation::motion() const
{
	return motion_;
}

const Animation::Matrices & Animation::local_matrices() const
{
	return local_matrices_;
}

int Animation::bone_const() const
{
	SkeletalMesh::bind(model_);
	return SkeletalMesh::end_time(motion_);
}

float Animation::end_time() const
{
	SkeletalMesh::bind(model_);
	return SkeletalMesh::end_time(motion_);
}
