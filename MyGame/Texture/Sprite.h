#ifndef SPRITE_H_
#define SPRITE_H_

#include <vector>
#include <unordered_map>
#include "../Math/Vector2.h"
#include "../Animation/AnimatedSprite.h"

// �X�v���C�g�N���X
class Sprite {
public:
    // ������
    static void initialize();
    // �摜�t�@�C���̓ǂݍ���
    static void load(int id, const std::string& file_name);
    // �摜�t�@�C���̓ǂݍ��� (�����w�肠��j
    static void load(int id, const std::string& file_name, int row, int column);
    // �o�C���h
    static void bind(int id);
    // �`��i�摜�S�́j
    static void draw(const Vector2& position);
    // �`��i�摜�̂P������`��j
    static void draw(const Vector2& position, int x, int y, int w, int h);
    // �`��i�����ԍ��w��j
    static void draw(int div_no, const Vector2& position, const Vector2& center = Vector2::Zero, const Vector2& scale = Vector2::One, float rotation = 0.0f);
    // �`��i�A�j���[�V�����w��j
    static void draw(int animation, float time, const Vector2& position, const Vector2& center = Vector2::Zero, const Vector2& scale = Vector2::One, float rotation = 0.0f);
    // �A�j���[�V�����̒ǉ�
    static void add_animation(int animation, int start, int end, float time);
    // �L�[�t���[����ǉ�
    static void add_key_frame(int animation, float time, int div_no);
    // �L�[�t���[����ǉ�
    static void add_key_frame(int animation, float time, int x, int y, int w, int h);
    // �X�v���C�g�̍폜
    static void erase(int id);
    // �A�j���[�V�����̏I�����Ԃ��擾
    static float get_animation_end_time(int animation);
    // �I������
    static void finalize();

private:
    // �o�C���h���̂h�c
    static int  id_;
    // �X�v���C�g�f�[�^
    static std::unordered_map<int, AnimatedSprite> sprite_map_;
};

#endif

// end of file
