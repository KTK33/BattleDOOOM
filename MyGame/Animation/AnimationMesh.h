#ifndef ANIMATION_MESH_H_
#define ANIMATION_MESH_H_

#include "../Mesh/SkeletalMesh.h"
#include "Animation.h"
//�A�j���[�V�����t�����b�V���N���X
class AnimatedMesh
{
public:
	//�R���X�g���N�^
	AnimatedMesh(int mesh, int motion = 0);
	//�X�V
	void update(float deltaTime);
	//�`��
	void draw() const;
	//���[�V�����̕ύX
	void change_motion(int motion);
	//�X�P���g���̕ϊ��s����v�Z����
	void transform(const Matrix& world);
	//�ϊ��s����擾
	const Matrix& bone_matrix(int no) const;
	//���[�V�����̏I�����Ԃ��擾
	float motion_end_time() const;

private:
	//�X�P���g���ϊ��s��
	using BoneMatrices = std::array<Matrix, 256>;
	//���b�V��
	int mesh_;
	//�A�j���[�V����
	Animation animation_;
	//�X�P���g���ϊ��s��
	BoneMatrices world_matrices_;
};
#endif // !ANIMATION_MESH_H_
