#include "CollisionMesh.h"
#include "../Collision/CollisionTriangle.h"
#include <DxLib.h>

// �o�C���h���̃��f��
int CollisionMesh::model_{ -1 };
// ���f���A�Z�b�g
ModelAsset CollisionMesh::asset_;

// ������
void CollisionMesh::initialize() {
    finalize();
}

// �I������
void CollisionMesh::finalize() {
    asset_.clear();
    model_ = -1;
}

// �ǂݍ���
bool CollisionMesh::load(int id, const std::string & file_name, int frame, int div_x, int div_y, int div_z) {
    auto result = asset_.load(id, file_name);
    if (result) {
        // �Փ˔�������\�z
        MV1SetupCollInfo(asset_[id], frame, div_x, div_y, div_z);
    }
    return result;
}

// �`��
void CollisionMesh::draw() {
    MV1DrawModel(model_);
}

int CollisionMesh::ModelHandle()
{
	return model_;
}

// �폜
void CollisionMesh::erase(int id) {
    model_ = (model_ == asset_[id]) ? -1 : model_;
    asset_.erase(id);
}

// ���b�V���̃o�C���h
void CollisionMesh::bind(int id) {
    model_ = asset_[id];
}

// �����Ƃ̏Փ˔���
bool CollisionMesh::collide_line(const Vector3 & start, const Vector3 & end, Vector3 * point, Vector3 * normal) {
    const auto coll_poly = MV1CollCheck_Line(model_, -1, start, end);
    if (coll_poly.HitFlag == TRUE) {
        if (point != nullptr) {
            *point = coll_poly.HitPosition;
        }
        if (normal != nullptr) {
            *normal = coll_poly.Normal;
        }
        return true;
    }
    return false;
}

// ���̂Ƃ̏Փ˔���
bool CollisionMesh::collide_sphere(const Vector3 & center, float radius, Vector3 * result) {
    // ���ƃ��b�V���̏Փ˔���
    const auto coll_poly = MV1CollCheck_Sphere(model_, -1, center, radius);
    // �Փ˂��Ă��Ȃ���ΏI��
    if (coll_poly.HitNum == 0) {
        // �Փ˔���f�[�^�̍폜
        MV1CollResultPolyDimTerminate(coll_poly);
        return false;
    }
    VECTOR result_center = center;
    // �|���S���̕��ʏ�ɋ��̂̈ʒu��␳����
    for (int i = 0; i < coll_poly.HitNum; ++i) {
        // ���ʏ�̍��W�̍ŋߓ_���W�����߂�
        PLANE_POINT_RESULT plane_point_result;
        Plane_Point_Analyse(
            &coll_poly.Dim[i].Position[0],
            &coll_poly.Dim[i].Normal,
            &result_center,
            &plane_point_result);
        // �O�p�`�̓����ɕ��ʏ�̍��W�̍ŋߓ_���W�����邩���ׂ�
        if (CollisionTriangle(
            coll_poly.Dim[i].Position[0],
            coll_poly.Dim[i].Position[1],
            coll_poly.Dim[i].Position[2]).is_inside(plane_point_result.Plane_MinDist_Pos)) {
            // �@���x�N�g���̕����֋��̂������o��
            const auto distance = std::sqrt(plane_point_result.Plane_Pnt_MinDist_Square);
            const auto offset = VScale(coll_poly.Dim[i].Normal, radius - distance);
            result_center = VAdd(result_center, offset);
        }
    }
    // �|���S���̃G�b�W�ɏd�Ȃ��Ă���ꍇ�Ɉʒu��␳����
    for (int i = 0; i < coll_poly.HitNum; ++i) {
        CollisionTriangle(
            coll_poly.Dim[i].Position[0],
            coll_poly.Dim[i].Position[1],
            coll_poly.Dim[i].Position[2]).collide_edge_and_sphere(result_center, radius, &result_center);
    }
    // �␳��̍��W��ݒ�
    if (result != nullptr) {
        *result = result_center;
    }
    // �Փ˔���f�[�^�̍폜
    MV1CollResultPolyDimTerminate(coll_poly);
    return true;
}

bool CollisionMesh::collide_capsule(const Vector3 & start, const Vector3 & end, float radius, Vector3 * result)
{
	//�����������ǂ���
	bool isHit = false;

	//�n�_�A�I�_���擾
	VECTOR resultstart = start;
	VECTOR resultend = end;

	//��������ɂ��������o��������s��
	if (collide_sphere(resultend, radius, &Vector3::VECTORToVector3(resultend))) {
		//��������̉����o���x�N�g�����쐬
		Vector3 moveVecbottom = VSub(resultend, end);
		//�J�v�Z���̎n�_�ɉ����o����K�p
		resultstart = VAdd(resultstart, moveVecbottom);
		isHit = true;
	}
	//���������o�����_�̎n�_�A�I�_����ۑ�
	VECTOR savestart = resultstart;
	VECTOR saveend = resultend;

	//������ɂ��������o��������s��
	if (collide_sphere(resultstart, radius, &Vector3::VECTORToVector3(resultstart))) {
		//������̉����o���x�N�g�����쐬
		Vector3 moveVectop = VSub(resultstart, savestart);
		//�J�v�Z���̏I�_�ɉ����o����K�p
		resultend = VAdd(resultend, moveVectop);
		isHit = true;
	}
	//�����܂łŎn�_�I�_�̉����o��������

	//���S���v�Z���ĕԂ�
	//if(isHit)*result = (resultstart+ resultend)*0.5f;

	// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
	MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(model_, -1, resultstart, resultend, radius);

	for (int i = 0; i < HitDim.HitNum; i++) {
		VECTOR triangle[4]{
			HitDim.Dim[i].Position[0],
			HitDim.Dim[i].Position[1],
			HitDim.Dim[i].Position[2],
			HitDim.Dim[i].Position[0]
		};

		for (int loop = 0; loop < 3; loop++) {
			SEGMENT_SEGMENT_RESULT seg_seg_result;
			Segment_Segment_Analyse(&resultstart, &resultend, &triangle[i], &triangle[i + 1], &seg_seg_result);
			const auto distance = std::sqrt(seg_seg_result.SegA_SegB_MinDist_Square);
			if (distance <= radius) {
				isHit = true;
				VECTOR offset = VScale(VNorm(VSub(seg_seg_result.SegA_MinDist_Pos, seg_seg_result.SegB_MinDist_Pos)), radius - distance);
				resultstart = VAdd(resultstart, offset);
				resultend = VAdd(resultend, offset);
			}
		}
	}
	if (isHit)*result = (resultstart + resultend)*0.5f;

	//�|���S�����J������
	MV1CollResultPolyDimTerminate(HitDim);

	return isHit;

}

bool CollisionMesh::collide_capsule(const Vector3 & start1, const Vector3 & end1, float radius1, const Vector3 & start2, const Vector3 & end2, float radius2, Vector3 * result1, Vector3 * result2)
{
	//�����������ǂ���
	bool isHit = false;

	//�n�_�A�I�_���擾
	VECTOR resultstart1 = start1;
	VECTOR resultend1 = end1;
	VECTOR resultstart2 = start2;
	VECTOR resultend2 = end2;

	if (collide_sphere(resultend1, radius1, &Vector3::VECTORToVector3(resultend1))) {
		//��������̉����o���x�N�g�����쐬
		Vector3 moveVecbottom = VSub(resultend1, end1);
		//�J�v�Z���̎n�_�ɉ����o����K�p
		resultend2 = VAdd(resultend2, moveVecbottom);
		isHit = true;
	}
	if (collide_sphere(resultend2, radius2, &Vector3::VECTORToVector3(resultend2))) {
		//��������̉����o���x�N�g�����쐬
		Vector3 moveVecbottom2 = VSub(resultend2, end2);
		//�J�v�Z���̎n�_�ɉ����o����K�p
		resultend1 = VAdd(resultend1, moveVecbottom2);
		isHit = true;
	}

	//���S���v�Z���ĕԂ�
	if (isHit) {
		*result1 = resultend1;
		*result2 = resultend2;
	}
	return isHit;

}
