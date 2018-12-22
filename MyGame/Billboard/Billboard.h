#ifndef BILLBOARD_H_
#define BILLBOARD_H_

#include "../Texture/TextureAsset.h"
#include "../Math/Vector3.h"
#include <string>

// �r���{�[�h�N���X
class Billboard {
public:
    // ������
    static void initialize();
    // �I������
    static void finalize();
    // �ǂݍ���
    static bool load(int id, const std::string& file_name);
    // �폜
    static void erase(int id);
    // �o�C���h
    static void bind(int id);
    // �`��
    static void draw(const Vector3& position, float size, float cx = 0.5f, float cy = 0.5f, float angle = 0.0f);

private:
    // �o�C���h���̃C���[�W
    static int          image_;
    // �C���[�W�A�Z�b�g
    static TextureAsset asset_;
};

#endif