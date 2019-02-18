#ifndef COLLISION_MESH_H_
#define COLLISION_MESH_H_

#include <string>
#include "../Math/Vector3.h"
#include "../Model/ModelAsset.h"
// �Փ˔���p���b�V���N���X
class CollisionMesh {
public:
	// ������
    static void initialize();
    // �I������
    static void finalize();
    // �ǂݍ���
    static bool load(int id, const std::string& file_name, int frame = -1, int div_x = 32, int div_y = 8, int div_z = 32);
    // �폜
    static void erase(int id);
    // ���b�V���̃o�C���h
    static void bind(int id);
    // �`��
    static void draw();

	static int ModelHandle();
    // �����Ƃ̏Փ˔���
    static bool collide_line(const Vector3& start, const Vector3& end, Vector3* point = nullptr, Vector3* normal = nullptr);
    // ���̂Ƃ̏Փ˔���
    static bool collide_sphere(const Vector3& center, float radius, Vector3* result = nullptr);

	static bool collide_capsule(const Vector3& start, const Vector3& end, float radius, Vector3* result = nullptr);

	static bool collide_capsule(const Vector3& start1, const Vector3& end1, float radius1, const Vector3& start2, const Vector3& end2, float radius2, Vector3* result1 = nullptr, Vector3* result2 = nullptr);

//private:
    // �Փ˔���p���f���n���h��
    static int  model_;
    // ���f���A�Z�b�g
    static ModelAsset asset_;
};

#endif